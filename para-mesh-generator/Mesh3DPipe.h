#pragma once
#include "Mesh3DTubular.h"
#include "PipeGeometry3D.h"

class Mesh3DPipe :
	public Mesh3DTubular, public PipeGeometry3D
{
private:
	Mesh3DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, double _height, double _revAng = -1.0);
public:
	Mesh3DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, double _height, const glm::ivec3& _nnodes, double _revAng = -1.0);
	Mesh3DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, double _height, const glm::dvec3& _elsize, double _revAng = -1.0);

	glm::dvec3 getCoords(int ir, int iy, int iz);

};

