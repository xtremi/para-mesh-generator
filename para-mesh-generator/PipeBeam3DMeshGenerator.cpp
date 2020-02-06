#include "PipeBeam3DMeshGenerator.h"
PipeBeam3DMeshGenerator::PipeBeam3DMeshGenerator(){
	valid_parameters = { "h", "ri", "ro", "elsize" };
	param_values = { &h,  &ri,  &ro,  &elsize };
}
PipeBeam3DMeshGenerator::~PipeBeam3DMeshGenerator(){}

int PipeBeam3DMeshGenerator::generate() {

	Mesh3DPipe* pipeMesh = new Mesh3DPipe(glm::dvec3(0.0), ri, ro, h, glm::dvec3(elsize), 0.4*2.0*M_PI);
	//Mesh3DElipsToRec* innerMesh = new Mesh3DElipsToRec(glm::dvec2(0.4*ri), glm::dvec2(0.8*ri), h, glm::dvec3(elsize));
	nodeRegions.push_back(pipeMesh);
	//nodeRegions.push_back(innerMesh);
	return 0;
}


int PipeBeam3DMeshGenerator::calculateInitalVariables() {
	return 0;
}

void PipeBeam3DMeshGenerator::writeConnectionElements(std::ofstream& file) {

}