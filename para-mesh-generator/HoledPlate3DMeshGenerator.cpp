#pragma once
#include "HoledPlate3DMeshGenerator.h"


HoledPlate3DMeshGenerator::HoledPlate3DMeshGenerator(const std::string& _filepath, format_type _format)
	: MeshGenerator(_filepath, _format) 
{
	valid_parameters = { "h", "rx", "ry", "sx", "sy", "elsize" };
	param_values	 = { &h,  &rx,  &ry,  &sx,  &sy,   &elsize };
}

int HoledPlate3DMeshGenerator::generate() {
	glm::dvec3 p0(0.0);
	glm::dvec2 rad(rx, ry);
	glm::dvec2 sqr(sx, sy);
	glm::dvec3 els(elsize);
	
	Mesh3DPipe*		pipe  = new Mesh3DPipe(p0, rad.x, rad.x*1.4, h, els);
	glm::ivec3 nnodes = pipe->getNnodes();
	nnodes.x *=4;
	Mesh3DElipsToRec* plate = new Mesh3DElipsToRec(p0, sqr, rad*1.4 + pipe->elsizex(), h, nnodes);

	nodeRegions.push_back(pipe);
	nodeRegions.push_back(plate);

	return 0;
}

int HoledPlate3DMeshGenerator::calculateInitalVariables(){
	return 0;
}

void HoledPlate3DMeshGenerator::writeConnectionElements() {
	Mesh3DTubular*		pipe = (Mesh3DTubular*)nodeRegions[0];
	Mesh3DTubular*		plate = (Mesh3DTubular*)nodeRegions[1];

	int elID = nodeRegions[1]->numberOfElements() + nodeRegions[1]->firstElementID();
	createElementsBetweenTube(feaWriter, plate, pipe, elID);
}