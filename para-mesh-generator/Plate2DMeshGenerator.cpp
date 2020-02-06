#include "Plate2DMeshGenerator.h"

Plate2DMeshGenerator::Plate2DMeshGenerator()
{
	valid_parameters = { "w", "h", "A", "freq", "elsize" };
	param_values = { &w, &h, &A, &freq, &elsize };
}

int Plate2DMeshGenerator::generate() {
	
	Mesh2DPlate* plate = new Mesh2DPlate(glm::dvec3(0.0), glm::dvec2(w, h), A, freq, glm::dvec2(elsize));
	nodeRegions.push_back(plate);
	return 0;
}
int Plate2DMeshGenerator::calculateInitalVariables() {
	return 0;
}

void Plate2DMeshGenerator::writeConnectionElements(std::ofstream& file) {}