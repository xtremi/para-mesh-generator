#include "MeshSideRefinement2D.h"

MeshSideRefinement2D::MeshSideRefinement2D(const glm::dvec2& size, int _refRows, double _elSizeNorm, double	_elSizeRef)
	: MeshSideRefinement(size, _refRows, _elSizeNorm, _elSizeRef)
{}
MeshSideRefinement2D::MeshSideRefinement2D(const glm::dvec2& size, int _refRows, double _elSizeNorm, int	_refFactor)
	: MeshSideRefinement(size, _refRows, _elSizeNorm, _refFactor)
{}

int MeshSideRefinement2D::writeRefinementNodes(
	FEAwriter*			feaWriter,
	const glm::dvec3&	spos,
	int					nodeIDstart)
{
	int nodeID = nodeIDstart;
	glm::dvec3 coords(spos);
	//coords.y += (l_ref + elsizeRef * yfac);
	int		currentNodesPerRow = nnodesRef;
	double	currentElsize = elsizeRef;
	int		currentRefFactor = 1;

	while (currentRefFactor < refFactor) {
		nRefinements++;

		//row b:
		nodeID = feaWriter->writeNodeRowX(coords, currentElsize, currentNodesPerRow, nodeID);

		coords.y += currentElsize * yfac;
		//row m:
		for (int i = 0; i < currentNodesPerRow; i++) {
			coords.x = (double)i*currentElsize;
			if (i % 4)
				feaWriter->writeNode(nodeID++, coords);
		}
		coords.y += currentElsize * yfac;
		coords.x = 0.0;

		currentRefFactor *= 2;
		currentNodesPerRow = (nnodesRef - 1) / currentRefFactor + 1;
		currentElsize = currentRefFactor * elsizeRef;

		//row t:		
		nodeID = feaWriter->writeNodeRowX(coords, currentElsize, currentNodesPerRow, nodeID);
		coords.y += currentElsize * yfac;
	}
	return nodeID;
}

int MeshSideRefinement2D::writeRefinementElements(FEAwriter* feaWriter, int elementID1, int nodeID1)
{
	int currentRefFactor = 1;
	int	currentNodesPerRow = nnodesRef;

	int elID = elementID1;
	int c = nodeID1;
	int n[4];
	for (int r = 0; r < nRefinements; r++) {

		//elRow b
		for (int i = 0; i < (currentNodesPerRow - 1); i++) {
			n[0] = c++;							n[1] = n[0] + 1;
			n[2] = n[1] + currentNodesPerRow;	n[3] = n[2] - 1;
			feaWriter->write4nodedShell(elID++, n);
		}
		c++;
		//elRow m + t 
		int nnodesRowM = 3 * (currentNodesPerRow - 1) / 4;
		for (int i = 0; i < (currentNodesPerRow - 1); i += 4) {

			int b0 = c;
			int m0 = b0 + currentNodesPerRow - i / 4;
			int t0 = m0 + nnodesRowM - i / 4;

			int b[5] = { b0, b0 + 1, b0 + 2, b0 + 3 , b0 + 4 };
			int m[3] = { m0, m0 + 1, m0 + 2 };
			int t[3] = { t0, t0 + 1, t0 + 2 };

			std::vector<int*> elNodes;
			int n1[4] = { b[0], b[1], m[0], t[0] }; elNodes.push_back(n1);
			int n2[4] = { b[1], b[2], m[1], m[0] }; elNodes.push_back(n2);
			int n3[4] = { b[2], b[3], m[2], m[1] }; elNodes.push_back(n3);
			int n4[4] = { b[3], b[4], t[2], m[2] }; elNodes.push_back(n4);
			int n5[4] = { m[0], m[1], t[1], t[0] }; elNodes.push_back(n5);
			int n6[4] = { m[1], m[2], t[2], t[1] }; elNodes.push_back(n6);

			for (int i = 0; i < 6; i++)
				feaWriter->write4nodedShell(elID++, elNodes[i]);
			c += 4;
		}

		currentRefFactor *= 2;
		currentNodesPerRow = (nnodesRef - 1) / currentRefFactor + 1;
		c += (nnodesRowM + 1);
	}
	return elID;
}