#pragma once
#include "MeshGenerator.h"
#include "Mesh3DPipe.h"

//#include "Mesh3DElipsToRec.h"

class PipeBeam3DMeshGenerator :
	public MeshGenerator
{
public:
	PipeBeam3DMeshGenerator(const std::string& _filepath, format_type _format);
	~PipeBeam3DMeshGenerator();

	int generate();

private:
	double h = 0.0;
	double ri = 5.0;
	double ro = 5.0;
	double elsize = 0.5;

	int calculateInitalVariables();

	void writeConnectionElements();

};

