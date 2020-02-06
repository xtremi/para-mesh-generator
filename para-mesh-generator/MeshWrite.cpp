#pragma once
#include "MeshWrite.h"

int writeElementRow(
	std::ofstream& file, format_type format,
	const std::vector<int>& bl,
	const std::vector<int>& br,
	const std::vector<int>& tr,
	const std::vector<int>& tl,
	int elStartID) {

	int n[8];
	int id = elStartID;
	for (int i = 0; i < bl.size() - 1; i++) {
		n[0] = bl[i];		n[1] = br[i];
		n[2] = br[i + 1];	n[3] = bl[i + 1];
		n[4] = tl[i];		n[5] = tr[i];
		n[6] = tr[i + 1];	n[7] = tl[i + 1];
		write8nodedHexa(file, id++, n, format);
	}
	return id;
}


int writeNodePlaneXY(
	std::ofstream&		file,
	format_type			format,
	const glm::dvec3&	spos,
	const glm::dvec2&	dxy,
	const glm::ivec2&	nnodes,
	int nodeIDstart) 
{
	glm::dvec3 coords = spos;
	int nodeID = nodeIDstart;
	for(int iy = 0; iy < nnodes.y; iy++)
	{
		for (int ix = 0; ix < nnodes.x; ix++) {
			writeNode(file, nodeID++, coords, format);
			coords.x += dxy.x;
		}
		coords.y += dxy.y;
		coords.x = spos.x;
	}
	return nodeID;
}

int writeNodePlaneXZ(
	std::ofstream&		file,
	format_type			format,
	const glm::dvec3&	spos,
	const glm::dvec2&	dxz,
	const glm::ivec2&	nnodes,
	int nodeIDstart)
{
	glm::dvec3 coords = spos;
	int nodeID = nodeIDstart;
	for (int iz = 0; iz < nnodes.y; iz++)
	{
		for (int ix = 0; ix < nnodes.x; ix++) {
			writeNode(file, nodeID++, coords, format);
			coords.x += dxz.x;
		}
		coords.z += dxz.y;
		coords.x = spos.x;
	}
	return nodeID;
}

int writeNodeCuboidXZY(
	std::ofstream&		file,
	format_type			format,
	const glm::dvec3&	spos,
	const glm::dvec3&	dxyz,
	const glm::ivec3&	nnodes,
	int nodeIDstart)
{
	glm::dvec3 coords = spos;
	int nodeID = nodeIDstart;
	for (int iy = 0; iy < nnodes.y; iy++)
	{
		for (int iz = 0; iz < nnodes.z; iz++)
		{
			for (int ix = 0; ix < nnodes.x; ix++) {
				writeNode(file, nodeID++, coords, format);
				coords.x += dxyz.x;
			}
			coords.x = 0.0;
			coords.z += dxyz.z;
		}
		coords.z = 0.0;
		coords.y += dxyz.y;
	}
	return nodeID;
}

int writeElementsPlaneXY(
	std::ofstream&		file, format_type			format,
	glm::ivec2			nnodes,
	int					nodeID1,
	int					elementID1
)
{
	int n[4];
	int c = nodeID1;
	int elID = elementID1;
	
	for (int iy = 0; iy < (nnodes.y - 1); iy++) {
		for (int ix = 0; ix < (nnodes.x - 1); ix++) {
			n[0] = c++;					n[1] = n[0] + 1;
			n[2] = n[1] + nnodes.x;	n[3] = n[2] - 1;
			write4nodedShell(file, elID++, n, format);
		}
		c++;
	}
	return elID;
}

int writeElementsCubeXZY(
	std::ofstream&		file,
	format_type			format,
	glm::ivec3			nnodes,
	int					nodeID1,
	int					elementID1
)
{
	int n[8];
	int c = nodeID1;
	int nNodesXZface = nnodes.x * nnodes.z;
	int elID = elementID1;
	bool stop = false;
	for (int iy = 0; iy < (nnodes.y - 1); iy++) {
		for (int iz = 0; iz < (nnodes.z - 1); iz++) {
			for (int ix = 0; ix < (nnodes.x - 1); ix++) {

				n[0] = c + nNodesXZface;
				n[1] = n[0] + 1;
				n[2] = c + 1;
				n[3] = c;
				n[4] = n[0] + nnodes.x;
				n[5] = n[4] + 1;
				n[6] = n[5] - nNodesXZface;
				n[7] = n[6] - 1;

				c++;
				write8nodedHexa(file, elID++, n, format);

				if (false && (elID > (3 * 16 * 5))) {
					stop = true;
					break;
				}
			}
			c++;
			if (stop) break;
		}
		c += nnodes.x;
		if (stop) break;
	}

	return elID;
}


int writeNodeRowX(std::ofstream& file, format_type format, const glm::dvec3& spos, double dx, int nrows, int nodeIDstart) {
	return writeNodeRow(file, format, spos, glm::dvec3(dx, 0.0, 0.0), nrows, nodeIDstart);
}
int writeNodeRowY(std::ofstream& file, format_type format, const glm::dvec3& spos, double dy, int nrows, int nodeIDstart) {
	return writeNodeRow(file, format, spos, glm::dvec3(0.0, dy, 0.0), nrows, nodeIDstart);
}
int writeNodeRowZ(std::ofstream& file, format_type format, const glm::dvec3& spos, double dz, int nrows, int nodeIDstart) {
	return writeNodeRow(file, format, spos, glm::dvec3(0.0, 0.0, dz), nrows, nodeIDstart);
}


int writeNodeRow(
	std::ofstream&		file,
	format_type			format,
	const glm::dvec3&	spos,
	const glm::dvec3& d, int nrows, int nodeIDstart)
{
	glm::dvec3 coords = spos;
	int nodeID = nodeIDstart;
	for (int i = 0; i < nrows; i++) {
		writeNode(file, nodeID++, coords, format);
		coords += d;
	}
	return nodeID;
}
