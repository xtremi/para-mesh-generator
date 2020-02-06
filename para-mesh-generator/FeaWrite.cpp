#pragma once
#include "FeaWrite.h"

/*
NODES
*/
void writeNode(std::ofstream& file, int nodeID, const glm::dvec3& c, format_type format) {
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
}


/*
NODES solver specific
*/
void writeNastranNode(std::ofstream& file, int nodeID, const glm::dvec3& c) {
	file << "GRID, " << nodeID << ",," << c.x << ", " << c.y << ", " << c.z << "\n";
}
void writeAbaqusNode(std::ofstream& file, int nodeID, const glm::dvec3& c) {
	file << " " << nodeID << ", " << c.x << ", " << c.y << ", " << c.z << "\n";
}
void writeAnsysNode(std::ofstream& file, int nodeID, const glm::dvec3& c) {
	file << "n, " << nodeID << ", " << c.x << ", " << c.y << ", " << c.z << "\n";
}

/*
SHELL ELEMENT
*/
void write4nodedShell(std::ofstream& file, int elID, int n[4], format_type format) {
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
}

/*
SOLID ELEMENT
*/
void write8nodedHexa(std::ofstream& file, int elID, int n[8], format_type format) {
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
}

/*
ABAQUS elements
*/
void writeAbaqusS4R(std::ofstream& file, int elID, int n[4]) {
	file << elID;
	writeCommaDelim(file, n, 4);
	file << "\n";
}
void writeAbaqusC3D8R(std::ofstream& file, int elID, int n[8]) {
	file << elID;
	writeCommaDelim(file, n, 8);
	file << "\n";
}


/*
NASTRAN elements
*/
void writeNastranCquad4(std::ofstream& file, int elID, int n[4]) {
	file << "CQUAD4," << elID << ",";
	writeCommaDelim(file, n, 4);
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
}

/*
ANSYS elements
*/
void writeAnsysShell181(std::ofstream& file, int elID, int n[4]) {
	file << "en, " << elID;
	writeCommaDelim(file, n, 4);
	file << "\n";
}
void writeAnsysSolid185(std::ofstream& file, int elID, int n[8]) {
	file << "en, " << elID;
	writeCommaDelim(file, n, 8);
	file << "\n";
}

/*
convenient functions
*/
void writeCommaDelim(std::ofstream& file, int* vec, int size) {
	for (int i = 0; i < size; i++)
		file << ", " << vec[i];
}