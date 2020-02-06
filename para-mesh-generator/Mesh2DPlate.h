#pragma once
#include "Mesh2DRectangle.h"

class Mesh2DPlate :
	public Mesh2DRectangle
{
private:
	Mesh2DPlate(const glm::dvec3& _pos, const glm::dvec2& _length, double _amp, double _freq);

public:
	Mesh2DPlate(const glm::dvec3& _pos, const glm::dvec2& _length, double _amp, double _freq, const glm::dvec2& elsize);

	glm::dvec3 getCoords(int ix, int iy);
	void writeNodes(std::ofstream& file, format_type format);
	void writeElements(std::ofstream& file, format_type format);

	int numberOfNodes();
	int numberOfElements();

private:
	glm::dvec2 elsize;
	glm::ivec2 nnodes;

	double amplitude;
	double freq;

	std::vector<double> ys;
	std::vector<double> zs;
	void defineYZvalues();

	double b;

};

