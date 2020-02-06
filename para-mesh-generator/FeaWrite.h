#include <fstream>
#include <string>
#include <iostream>
#include "string_utilities.h"
#include "mesh_types.h"
#include "glm/glm.hpp"

void writeNode(std::ofstream& file, int nodeID, const glm::dvec3& c, format_type format);
void write4nodedShell(std::ofstream& file, int elID, int n[4], format_type format);
void write8nodedHexa(std::ofstream& file, int elID, int n[8], format_type format);


void writeNastranNode(std::ofstream& file, int nodeID, const glm::dvec3& c);
void writeAbaqusNode(std::ofstream& file, int nodeID, const glm::dvec3& c);
void writeAnsysNode(std::ofstream& file, int nodeID, const glm::dvec3& c);

void writeAbaqusS4R(std::ofstream& file, int elID, int n[4]);
void writeAbaqusC3D8R(std::ofstream& file, int elID, int n[8]);

void writeNastranCquad4(std::ofstream& file, int elID, int n[4]);
void writeNastranChexa8(std::ofstream& file, int elID, int n[8]);

void writeAnsysShell181(std::ofstream& file, int elID, int n[4]);
void writeAnsysSolid185(std::ofstream& file, int elID, int n[8]);

void writeCommaDelim(std::ofstream& file, int* vec, int size);