#pragma once
#include "FeaWrite.h"

/*
convenient functions
*/
void writeVectorCommaDelimeted(std::ofstream& file, int* vec, int size) {
	for (int i = 0; i < size; i++)
		file << ", " << vec[i];
}

void writeVectorSpaceDelimeted(std::ofstream& file, int* vec, int size) {
	for (int i = 0; i < size; i++)
		file << " " << vec[i];
}


/*********************************/
/*    NASTRAN                    */
/*********************************/
void NastranFEAwriter::writeNode(int nodeID, const glm::dvec3& c) {
	(*file) << "GRID, " << nodeID << ",," << c.x << ", " << c.y << ", " << c.z << "\n";
}
void NastranFEAwriter::write4nodedShell(int elID, int n[4]) {
	(*file) << "CQUAD4," << elID << ",";
	writeVectorCommaDelimeted((*file), n, 4);
	(*file) << "\n";
}
void NastranFEAwriter::write8nodedHexa(int elID, int n[8]) {
	(*file) << "CHEXA," << elID << ",";
	for (int j = 0; j < 8; j++) {
		if (j == 6)
			(*file) << ",\n,";
		else
			(*file) << ", ";
		(*file) << n[j];
	}
	(*file) << "\n";
}


/*********************************/
/*    ABAQUS                     */
/*********************************/
void AbaqusFEAwriter::writeNode(int nodeID, const glm::dvec3& c) {
	(*file) << " " << nodeID << ", " << c.x << ", " << c.y << ", " << c.z << "\n";
}
void AbaqusFEAwriter::write4nodedShell(int elID, int n[4]) {
	(*file) << elID;
	writeVectorCommaDelimeted((*file), n, 4);
	(*file) << "\n";
}
void AbaqusFEAwriter::write8nodedHexa(int elID, int n[8]) {
	(*file) << elID;
	writeVectorCommaDelimeted((*file), n, 8);
	(*file) << "\n";
}

void AbaqusFEAwriter::writePreNodes(int numberOfNodes) {
	(*file) << "*Node\n";
}
void AbaqusFEAwriter::writePreElements(int numberOfElements) {
	if (eldim == element_dim_type::e2D)
		(*file) << "*Element, type=S4R\n";
	else
		(*file) << "*Element, type=C3D8R\n";
}

/*********************************/
/*    ANSYS                      */
/*********************************/
void AnsysFEAwriter::writeNode(int nodeID, const glm::dvec3& c) {
	(*file) << "n, " << nodeID << ", " << c.x << ", " << c.y << ", " << c.z << "\n";
}
void AnsysFEAwriter::write4nodedShell(int elID, int n[4]) {
	(*file) << "en, " << elID;
	writeVectorCommaDelimeted((*file), n, 4);
	(*file) << "\n";
}
void AnsysFEAwriter::write8nodedHexa(int elID, int n[8]) {
	(*file) << "en, " << elID;
	writeVectorCommaDelimeted((*file), n, 8);
	(*file) << "\n";
}

void AnsysFEAwriter::writePreNodes(int numberOfNodes){
	(*file) << "/prep7\n";
}
void AnsysFEAwriter::writePreElements(int numberOfElements){
	if (eldim == element_dim_type::e2D)
		(*file) << "et, 1, SHELL181\nsectype, 1, SHELL,, S3D\nsecnum, 1\ntype, 1\n";
	else
		(*file) << "et, 1, SOLID185\ntype, 1\n";
}


/*********************************/
/*    VTK                        */
/*********************************/
void VTKFEAwriter::writeNode(int nodeID, const glm::dvec3& c) {
	(*file) << c.x << " " << c.y << " " << c.z << "\n";
}
void VTKFEAwriter::write4nodedShell(int elID, int n[4]) {
	writeVectorSpaceDelimeted((*file), n, 4);
	(*file) << "\n";
}
void VTKFEAwriter::write8nodedHexa(int elID, int n[8]) {
	writeVectorSpaceDelimeted((*file), n, 8);
	(*file) << "\n";
}

void VTKFEAwriter::writePreNodes(int numberOfNodes) {
	
}
void VTKFEAwriter::writePreElements(int numberOfElements) {

}

/*********************************/
/*    FEAwriter general          */
/*********************************/
int FEAwriter::writeElementRow(
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
		write8nodedHexa(id++, n);
	}
	return id;
}


int FEAwriter::writeNodePlaneXY(
	const glm::dvec3&	spos,
	const glm::dvec2&	dxy,
	const glm::ivec2&	nnodes,
	int nodeIDstart)
{
	glm::dvec3 coords = spos;
	int nodeID = nodeIDstart;
	for (int iy = 0; iy < nnodes.y; iy++)
	{
		for (int ix = 0; ix < nnodes.x; ix++) {
			writeNode(nodeID++, coords);
			coords.x += dxy.x;
		}
		coords.y += dxy.y;
		coords.x = spos.x;
	}
	return nodeID;
}

int FEAwriter::writeNodePlaneXZ(
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
			writeNode(nodeID++, coords);
			coords.x += dxz.x;
		}
		coords.z += dxz.y;
		coords.x = spos.x;
	}
	return nodeID;
}

int FEAwriter::writeNodePlaneYZ(
	const glm::dvec3&	spos,
	const glm::dvec2&	dyz,
	const glm::ivec2&	nnodes,
	int nodeIDstart)
{
	glm::dvec3 coords = spos;
	int nodeID = nodeIDstart;
	for (int iz = 0; iz < nnodes[1]; iz++)
	{
		for (int iy = 0; iy < nnodes[0]; iy++) {
			writeNode(nodeID++, coords);
			coords.y += dyz[0];
		}
		coords.z += dyz[1];
		coords.x = spos.x;
	}
	return nodeID;
}

int FEAwriter::writeNodeCuboidXZY(
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
				writeNode(nodeID++, coords);
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

int FEAwriter::writeElementsPlaneXY(
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
			write4nodedShell(elID++, n);
		}
		c++;
	}
	return elID;
}

int FEAwriter::writeElementsCubeXZY(
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
				write8nodedHexa(elID++, n);

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


int FEAwriter::writeNodeRowX(const glm::dvec3& spos, double dx, int nrows, int nodeIDstart) {
	return writeNodeRow(spos, glm::dvec3(dx, 0.0, 0.0), nrows, nodeIDstart);
}
int FEAwriter::writeNodeRowY(const glm::dvec3& spos, double dy, int nrows, int nodeIDstart) {
	return writeNodeRow(spos, glm::dvec3(0.0, dy, 0.0), nrows, nodeIDstart);
}
int FEAwriter::writeNodeRowZ(const glm::dvec3& spos, double dz, int nrows, int nodeIDstart) {
	return writeNodeRow(spos, glm::dvec3(0.0, 0.0, dz), nrows, nodeIDstart);
}


int FEAwriter::writeNodeRow(
	const glm::dvec3&	spos,
	const glm::dvec3&	d, 
	int					nrows, 
	int					nodeIDstart)
{
	glm::dvec3 coords = spos;
	int nodeID = nodeIDstart;
	for (int i = 0; i < nrows; i++) {
		writeNode(nodeID++, coords);
		coords += d;
	}
	return nodeID;
}



/*
ABAQUS elements
*/
/*void writeAbaqusS4R(std::ofstream& file, int elID, int n[4]) {
	file << elID;
	writeVectorCommaDelimeted(file, n, 4);
	file << "\n";
}
void writeAbaqusC3D8R(std::ofstream& file, int elID, int n[8]) {
	file << elID;
	writeVectorCommaDelimeted(file, n, 8);
	file << "\n";
}*/


/*
NASTRAN elements
*/
/*void writeNastranCquad4(std::ofstream& file, int elID, int n[4]) {
	file << "CQUAD4," << elID << ",";
	writeVectorCommaDelimeted(file, n, 4);
	file << "\n";
}
void writeNastranChexa8(std::ofstream& file, int elID, int n[8]) {
	file << "CHEXA," << elID << ",";
	for (int j = 0; j < 8; j++) {
		if (j == 6)
			file << ",\n,";
		else
			file << ", ";
		file << n[j];
	}
	file << "\n";
}*/

/*
ANSYS elements
*/
/*void writeAnsysShell181(std::ofstream& file, int elID, int n[4]) {
	file << "en, " << elID;
	writeVectorCommaDelimeted(file, n, 4);
	file << "\n";
}
void writeAnsysSolid185(std::ofstream& file, int elID, int n[8]) {
	file << "en, " << elID;
	writeVectorCommaDelimeted(file, n, 8);
	file << "\n";
}*/

/*
VTK elements
*/
/*void writeVTKQuad9(std::ofstream& file, int elID, int n[4]) {
	writeVectorSpaceDelimeted(file, n, 4);
	file << "\n";
}
void writeVTKHexahedron12(std::ofstream& file, int elID, int n[8]) {
	writeVectorSpaceDelimeted(file, n, 8);
	file << "\n";
}*/


/*
NODES
*/
/*void writeNode(std::ofstream& file, int nodeID, const glm::dvec3& c, format_type format) {
	switch (format)
	{
	case format_type::ANSYS:
		writeAnsysNode(file, nodeID, c);
		break;
	case format_type::NASTRAN:
		writeNastranNode(file, nodeID, c);
		break;
	case format_type::ABAQUS:
		writeAbaqusNode(file, nodeID, c);
		break;
	default:
		break;
	}
}*/


/*
NODES solver specific
*/
/*void writeNastranNode(std::ofstream& file, int nodeID, const glm::dvec3& c) {
	file << "GRID, " << nodeID << ",," << c.x << ", " << c.y << ", " << c.z << "\n";
}
void writeAbaqusNode(std::ofstream& file, int nodeID, const glm::dvec3& c) {
	file << " " << nodeID << ", " << c.x << ", " << c.y << ", " << c.z << "\n";
}
void writeAnsysNode(std::ofstream& file, int nodeID, const glm::dvec3& c) {
	file << "n, " << nodeID << ", " << c.x << ", " << c.y << ", " << c.z << "\n";
}
void writeVTKNode(std::ofstream& file, int nodeID, const glm::dvec3& c) {

}*/


/*
SHELL ELEMENT
*/
/*void write4nodedShell(std::ofstream& file, int elID, int n[4], format_type format) {
	switch (format)
	{
	case format_type::ANSYS:
		writeAnsysShell181(file, elID, n);
		break;
	case format_type::NASTRAN:
		writeNastranCquad4(file, elID, n);
		break;
	case format_type::ABAQUS:
		writeAbaqusS4R(file, elID, n);
		break;
	default:
		break;
	}
}*/

/*
SOLID ELEMENT
*/
/*void write8nodedHexa(std::ofstream& file, int elID, int n[8], format_type format) {
	switch (format)
	{
	case format_type::ANSYS:
		writeAnsysSolid185(file, elID, n);
		break;
	case format_type::NASTRAN:
		writeNastranChexa8(file, elID, n);
		break;
	case format_type::ABAQUS:
		writeAbaqusC3D8R(file, elID, n);
		break;
	default:
		break;
	}
}*/


