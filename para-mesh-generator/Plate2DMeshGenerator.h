#pragma once
#include "MeshGenerator.h"
#include "Mesh2DPlate.h"

class Plate2DMeshGenerator :
	public MeshGenerator
{
public:
	Plate2DMeshGenerator();

	int generate();
private:
	double w = 0.0;
	double h = 5.0;
	double elsize = 0.5;
	double A = 0.0;
	double freq = 1.0;

	int calculateInitalVariables();

	void writeConnectionElements(std::ofstream& file);
};

