#include "MeshSideRefinement3D.h"


MeshSideRefinement3D::MeshSideRefinement3D(const glm::dvec3& size, int _refRows, double _elSizeNorm, double	_elSizeRef)
	: MeshCircularRefinement(glm::dvec2(size.x, size.y), _refRows, _elSizeNorm, _elSizeRef)
{
	elsizeRefZ = elsizeRef;
	correctRefZElementSizeAndNumbers(size.z);
	normZelementSizeAndNumbersFromRefFactor(size.z);
	calculateMeshSectionLengths(size.y);
}
MeshSideRefinement3D::MeshSideRefinement3D(const glm::dvec3& size, int _refRows, double _elSizeNorm, int _refFactor)
	: MeshCircularRefinement(glm::dvec2(size.x, size.y), _refRows, _elSizeNorm, _refFactor)
{}

void MeshSideRefinement3D::correctRefZElementSizeAndNumbers(double lengthz)
{
	nnodesRefZ = (int)(lengthz / elsizeRefZ) + 1;
	nnodesRefZ = power_ceil(nnodesRefZ - 1) + 1;
	elsizeRefZ = lengthz / (double)(nnodesRefZ - 1);
}
void MeshSideRefinement3D::normZelementSizeAndNumbersFromRefFactor(double lengthz)
{
	elsizeNormZ = (double)refFactor * elsizeRefZ;
	nnodesNormZ = (int)(lengthz / elsizeNormZ) + 1;
}


int MeshSideRefinement3D::writeRefinementNodes(
	std::ofstream& file,
	format_type format,
	const glm::dvec3& spos,
	int nodeIDstart
)
{
	int nodeID = nodeIDstart;
	glm::dvec3 coords(spos);
	//coords.y += (l_ref + elsizeRef * yfac);
	int		currentNodesX = nnodesRef;
	int		currentNodesZ = nnodesRefZ;
	double	currentElsizeX = elsizeRef;
	double	currentElsizeY = elsizeRef;
	double	currentElsizeZ = elsizeRefZ;
	int		currentRefFactorX = 1;
	int		currentRefFactorZ = 1;

	while (currentRefFactorX < refFactor) {
		nRefinements++;

		//plane b:
		nodeID = writeNodePlaneXZ(file, format, coords, 
			glm::dvec2(currentElsizeX, currentElsizeZ), glm::ivec2(currentNodesX, currentNodesZ), nodeID);
		
		//row m1:
		coords.y += currentElsizeY * yfac;
		for (int i = 0; i < currentNodesX; i++) {
			coords.x = (double)i*currentElsizeX;
			if (i % 4)
				nodeID = writeNodeRowZ(file, format, coords, currentElsizeZ, currentNodesZ, nodeID);
		}

		//row m2:
		coords.y += currentElsizeY * yfac;
		coords.x = 0.0; coords.z = 0.0;

		currentRefFactorX *= 2;
		currentNodesX = (nnodesRef - 1) / currentRefFactorX + 1;
		currentElsizeX = currentRefFactorX * elsizeRef;

		nodeID = writeNodePlaneXZ(file, format, coords, glm::dvec2(currentElsizeX, currentElsizeZ), glm::ivec2(currentNodesX, currentNodesZ), nodeID);

		//row m3
		coords.y += currentElsizeY * yfac;
		coords.x = 0.0; coords.z = 0.0;

		for (int i = 0; i < currentNodesZ; i++) {
			coords.z = (double)i*currentElsizeZ;
			if (i % 4)
				nodeID = writeNodeRowX(file, format, coords, currentElsizeX, currentNodesX, nodeID++);
		}
		
		//row t:
		coords.y += currentElsizeY * yfac;
		coords.x = 0.0; coords.z = 0.0;

		currentRefFactorZ *= 2;
		currentNodesZ = (nnodesRefZ - 1) / currentRefFactorZ + 1;
		currentElsizeZ = currentRefFactorZ * elsizeRefZ;
			
		nodeID = writeNodePlaneXZ(file, format, coords,
			glm::dvec2(currentElsizeX, currentElsizeZ), glm::ivec2(currentNodesX, currentNodesZ), nodeID);
		
		currentElsizeY *= 2;
		coords.y += currentElsizeY * yfac;
	}
	return nodeID;
}

void MeshSideRefinement3D::calculateMeshSectionRefToNormLength()
{
	l_ref_to_norm = 0.0;
	int n = 1;
	while (n < refFactor) {
		l_ref_to_norm += 5.0*elsizeRef*(double)n;
		n *= 2;
	}
}

int MeshSideRefinement3D::writeRefinementElements(std::ofstream& file, format_type format, int elementID1, int nodeID1)
{
	int currentRefFactor = 1;
	int	currentNodesX = nnodesRef;
	int	currentNodesZ = nnodesRefZ;
	int elID = elementID1;
	int c = nodeID1;

	bool cancel = false;

	for (int r = 0; r < nRefinements; r++) {

		//Nnodes for next refinement:
		int nextNodesX = (currentNodesX - 1) / 2 + 1;
		int nextNodesZ = (currentNodesZ - 1) / 2 + 1;

		//Numbe of nodes on each plane:
		int nnodesPlaneB	= currentNodesX * currentNodesZ;
		int nnodesRowM1		= 3 * (currentNodesX - 1) / 4;
		int nnodesPlaneM1	= nnodesRowM1 * currentNodesZ;
		int nnodesPlaneM2	= nextNodesX * currentNodesZ;
		int nnodesRowM3     = 3 * (currentNodesZ - 1) / 4;
		int nnodesPlaneM3   = nnodesRowM3 * nextNodesX;
		int nnodesPlaneT    = nextNodesX * nextNodesZ;
		int nnodesTotal		= 2*nnodesPlaneB + nnodesPlaneM1 + nnodesPlaneM2 + nnodesPlaneM3 /*+ nnodesPlaneT*/;

		int firstNodePrevT = c;
		int firstNodeB	= firstNodePrevT + nnodesPlaneB;
		int firstNodeM1 = firstNodeB  + nnodesPlaneB;
		int firstNodeM2 = firstNodeM1 + nnodesPlaneM1;
		
		int firstNodeM2b = firstNodeM2;
		int firstNodeM3 = firstNodeM2 + nnodesPlaneM2;
		int firstNodeT  = firstNodeM3 + nnodesPlaneM3;

		//elPlane B:
		elID = writeElementsCubeXZY(file, format, glm::ivec3(currentNodesX, 2, currentNodesZ), firstNodePrevT, elID);

		for (int iz = 0; iz < (currentNodesZ - 1); iz++) {
			for (int i = 0; i < (currentNodesX - 1); i += 4) {

				//row b | m1 | m2 first nodes front:
				int bf_0 = firstNodeB + 4 * (i / 4);
				int m1f_0 = firstNodeM1 + 3 * (i / 4) * currentNodesZ;
				int m2f_0 = firstNodeM2 + 2 * (i / 4);

				//row b | m1 | m2 first nodes back:
				int bb_0 = bf_0 + currentNodesX;
				int m1b_0 = m1f_0 + 1;
				int m2b_0 = m2f_0 + nextNodesX;

				int bf[5] = { bf_0, bf_0 + 1, bf_0 + 2, bf_0 + 3 , bf_0 + 4 };
				int m1f[3] = { m1f_0, m1f_0 + currentNodesZ, m1f_0 + 2 * currentNodesZ };
				int m2f[3] = { m2f_0, m2f_0 + 1, m2f_0 + 2 };

				int bb[5] = { bb_0, bb_0 + 1, bb_0 + 2, bb_0 + 3 , bb_0 + 4 };
				int m1b[3] = { m1b_0, m1b_0 + currentNodesZ, m1b_0 + 2 * currentNodesZ };
				int m2b[3] = { m2b_0, m2b_0 + 1, m2b_0 + 2 };

				std::string tmp_nids = arrayToString(bf, 5) + arrayToString(m1f, 3) + arrayToString(m2f, 3);
				tmp_nids += (arrayToString(bb, 5) + arrayToString(m1b, 3) + arrayToString(m2b, 3));

				std::vector<int*> elNodes;
				int n_el1[8] = { bf[0], bf[1], bb[1], bb[0],  m2f[0], m1f[0], m1b[0], m2b[0] }; elNodes.push_back(n_el1);
				int n_el2[8] = { bf[1], bf[2], bb[2], bb[1],  m1f[0], m1f[1], m1b[1], m1b[0] }; elNodes.push_back(n_el2);
				int n_el3[8] = { bf[2], bf[3], bb[3], bb[2],  m1f[1], m1f[2], m1b[2], m1b[1] }; elNodes.push_back(n_el3);
				int n_el4[8] = { bf[3], bf[4], bb[4], bb[3],  m1f[2], m2f[2], m2b[2], m1b[2] }; elNodes.push_back(n_el4);

				int n_el5[8] = { m1f[0], m1f[1], m1b[1], m1b[0],  m2f[0], m2f[1], m2b[1], m2b[0] }; elNodes.push_back(n_el5);
				int n_el6[8] = { m1f[1], m1f[2], m1b[2], m1b[1],  m2f[1], m2f[2], m2b[2], m2b[1] }; elNodes.push_back(n_el6);

				for (int i = 0; i < elNodes.size(); i++)
					write8nodedHexa(file, elID++, elNodes[i], format);

				//if (!cancel) { cancel = true; break; }

			}
			if (cancel) { break; }
			firstNodeB += currentNodesX;
			firstNodeM1 += 1;
			firstNodeM2 += nextNodesX;
		}

		for (int ix = 0; ix < (nextNodesX- 1); ix++){
			for (int i = 0; i < (currentNodesZ - 1); i += 4){

				int m2f_0 = firstNodeM2b + 4 * (i / 4)* nextNodesX;
				int m3f_0 = firstNodeM3 + 3 * (i / 4) * nextNodesX;
				int tf_0 = firstNodeT + 2 * (i / 4)* nextNodesX;

				int m2f[5], m3f[3], tf[3];
				int m2b[5], m3b[3], tb[3];
				for (int i = 0; i < 5; i++) {
					m2f[i] = m2f_0 + i * nextNodesX;
					m2b[i] = m2f[i] + 1;
				}
				for (int i = 0; i < 3; i++) {
					m3f[i] = m3f_0 + i * nextNodesX;
					m3b[i] = m3f[i] + 1;
					tf[i] = tf_0 + i * nextNodesX;
					tb[i] = tf[i] + 1;
				}
				std::string tmp_nids = arrayToString(m2f, 5) + arrayToString(m3f, 3) + arrayToString(tf, 3);
				tmp_nids += (arrayToString(m2b, 5) + arrayToString(m3b, 3) + arrayToString(tb, 3));

				std::vector<int*> elNodes;
				int n_el1[8] = { m2f[0], m2f[1], m2b[1], m2b[0],  tf[0], m3f[0], m3b[0], tb[0] }; elNodes.push_back(n_el1);
				int n_el2[8] = { m2f[1], m2f[2], m2b[2], m2b[1],  m3f[0], m3f[1], m3b[1], m3b[0] }; elNodes.push_back(n_el2);
				int n_el3[8] = { m2f[2], m2f[3], m2b[3], m2b[2],  m3f[1], m3f[2], m3b[2], m3b[1] }; elNodes.push_back(n_el3);
				int n_el4[8] = { m2f[3], m2f[4], m2b[4], m2b[3],  m3f[2], tf[2], tb[2], m3b[2] }; elNodes.push_back(n_el4);

				int n_el5[8] = { m3f[0], m3f[1], m3b[1], m3b[0],  tf[0], tf[1], tb[1], tb[0] }; elNodes.push_back(n_el5);
				int n_el6[8] = { m3f[1], m3f[2], m3b[2], m3b[1],  tf[1], tf[2], tb[2], tb[1] }; elNodes.push_back(n_el6);

				for (int i = 0; i < elNodes.size(); i++)
					write8nodedHexa(file, elID++, elNodes[i], format);

				
			}
			if (cancel) { break; }
			firstNodeM2b += 1;
			firstNodeM3 += 1;
			firstNodeT += 1;
		}

		if (cancel) { break; }
		currentNodesX = nextNodesX;
		currentNodesZ = nextNodesZ;
		c += nnodesTotal;

	}
	return elID;
}

	
