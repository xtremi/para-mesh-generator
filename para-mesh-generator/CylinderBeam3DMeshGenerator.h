#pragma once
#include "MeshGenerator.h"
#include "Mesh3DPipe.h"
#include "Mesh3DElipsToRec.h"

class CylinderBeam3DMeshGenerator :
	public MeshGenerator
{
public:
	CylinderBeam3DMeshGenerator();
	~CylinderBeam3DMeshGenerator();

	int generate();
private:
	double h = 0.0;
	double ri = 5.0;
	double ro = 5.0;
	double elsize = 0.5;

	int calculateInitalVariables();

	void writeConnectionElements(std::ofstream& file);
};

