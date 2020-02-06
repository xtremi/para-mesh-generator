#pragma once
#include "MeshGenerator.h"
#include "Mesh3DElipsToRec.h"
#include "Mesh3DPipe.h"

class HoledPlate3DMeshGenerator 
	: public MeshGenerator
{
public:
	HoledPlate3DMeshGenerator();

	int generate();
private:
	double h = 0.0;
	double rx = 5.0;
	double ry = 5.0;
	double sx = 5.0;
	double sy = 5.0;
	double elsize = 0.5;

	int calculateInitalVariables();

	void writeConnectionElements(std::ofstream& file);
};

