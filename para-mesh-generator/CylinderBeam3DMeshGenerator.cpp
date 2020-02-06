#pragma once
#include "CylinderBeam3DMeshGenerator.h"

CylinderBeam3DMeshGenerator::CylinderBeam3DMeshGenerator() {
	valid_parameters = { "h", "ri", "ro", "elsize" };
	param_values = { &h,  &ri,  &ro,  &elsize };
}
CylinderBeam3DMeshGenerator::~CylinderBeam3DMeshGenerator() {}

int CylinderBeam3DMeshGenerator::generate() {

	Mesh3DPipe* pipeMesh = new Mesh3DPipe(glm::dvec3(0.0), ri, ro, h, glm::dvec3(elsize));
	double dr = pipeMesh->elsizey();
	glm::ivec3 nnodes = pipeMesh->getNnodes();
	nnodes.x *= 2;
	Mesh3DElipsToRec* innerMesh = new Mesh3DElipsToRec(glm::dvec3(0.0), glm::dvec2(0.4*ri), glm::dvec2(ri - dr), h, nnodes);
	nodeRegions.push_back(pipeMesh);
	nodeRegions.push_back(innerMesh);
	return 0;
}


int CylinderBeam3DMeshGenerator::calculateInitalVariables() {
	return 0;
}

void CylinderBeam3DMeshGenerator::writeConnectionElements(std::ofstream& file) {

	Mesh3DTubular*		pipe  = (Mesh3DTubular*)nodeRegions[0];
	Mesh3DTubular*		elRec = (Mesh3DTubular*)nodeRegions[1];

	int elID = nodeRegions[1]->numberOfElements() + nodeRegions[1]->firstElementID();
	createElementsBetweenTube(file, pipe, elRec, elID, format);
}