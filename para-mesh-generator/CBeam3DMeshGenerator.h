#pragma once
#include "MeshGenerator.h"
#include "Mesh3DCube.h"

class CBeam3DMeshGenerator :
	public MeshGenerator
{
public:
	CBeam3DMeshGenerator(const std::string& _filepath, format_type _format);
	~CBeam3DMeshGenerator();

	int generate();

private:
	double h = 10.0;
	double w_top = 10.0;
	double w_bot = 10.0;
	double t_top = 1.0;
	double t_bot = 1.0;
	double t_mid = 0.5;
	double r = 0.14;
	double l = 100.0;
	double elsize = 0.25;

	glm::dvec3 w1, ft1, ft2, ft3, fb1, fb2, fb3;

	int calculateInitalVariables();

	void writeConnectionElements();
};

