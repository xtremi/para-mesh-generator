#pragma once
#include "Mesh3DTubular.h"

class Mesh3DElipsToRec :
	public Mesh3DTubular
{
private:
	Mesh3DElipsToRec(const glm::dvec3& _pos, const glm::dvec2& _sqrdim, const glm::dvec2& _rad, double _height);

public:
	Mesh3DElipsToRec(const glm::dvec3& _pos, const glm::dvec2& _sqrdim, const glm::dvec2& _rad, double _height, const glm::ivec3& nnodes);
	Mesh3DElipsToRec(const glm::dvec3& _pos, const glm::dvec2& _sqrdim, const glm::dvec2& _rad, double _height, const glm::dvec3& elsize);

	glm::dvec3 getCoords(int ir, int iy, int iz);

private:
	glm::dvec2 sqrdim;
	glm::dvec2 rad;
	double height;
	int nnodesSx, nnodesSy;

	double dphi = 0.0;
	double innerPerimeter = 0.0;
	double outerPerimeter = 0.0;


};

