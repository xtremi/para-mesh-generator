#pragma once
#include "MeshGenerator.h"
#include "Mesh3DElipsToRec.h"
#include "Mesh3DPipe.h"

class HoledPlate3DMeshGenerator 
	: public MeshGenerator
{
public:
	HoledPlate3DMeshGenerator(const std::string& _filepath, format_type _format);

	int generate();
private:
	double h = 0.0;
	double rx = 5.0;
	double ry = 5.0;
	double sx = 5.0;
	double sy = 5.0;
	double elsize = 0.5;

	int calculateInitalVariables();

	void writeConnectionElements();
};

