#pragma once
#include "Mesh2DTubular.h"
#include "PipeGeometry2D.h"

class Mesh2DPipe :
	public Mesh2DTubular, public PipeGeometry2D
{
private:
	Mesh2DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, double _revAng);

public:
	Mesh2DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, const glm::ivec2& _nnodes, double _revAng = -1.0);
	Mesh2DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, const glm::dvec2& _elsize, double _revAng = -1.0);

	glm::dvec3 getCoords(int ir, int iy);

};

