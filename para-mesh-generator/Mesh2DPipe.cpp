#include "Mesh2DPipe.h"

Mesh2DPipe::Mesh2DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, double _revAng)
	: Mesh2DTubular(_pos, _revAng < 0.0) , PipeGeometry2D(_radInner, _radOuter, _revAng)
{

}

/*
	elsize.x = size along radius
	elsize.y = size along inner edge
*/
Mesh2DPipe::Mesh2DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, const glm::ivec2& _nnodes, double _revAng)
	: Mesh2DPipe(_pos, _radInner, _radOuter, _revAng)
{
	nnodes = _nnodes;
	nnodes.y = nnodes.y - nnodes.y % 8;

	double l = radOuter - radInner;
	elsize.x = l / ((double)nnodes.x - 1.0);
	elsize.y = innerPerimeter / (double)nnodes.y;

	dphi = revAng / (double)nnodes.y;
}


Mesh2DPipe::Mesh2DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, const glm::dvec2& _elsize, double _revAng)
	: Mesh2DPipe(_pos, _radInner, _radOuter, _revAng)
{
	elsize = _elsize;

	double l = radOuter - radInner;
	nnodes.x = (int)(l / elsize.x) + 1;
	nnodes.y = (int)(innerPerimeter / elsize.y);

	nnodes.y -= nnodes.y % 8;

	elsize.x = l / ((double)nnodes.x - 1.0);
	elsize.y = innerPerimeter / (double)nnodes.y;

	dphi = revAng / (double)nnodes.y;
}


glm::dvec3 Mesh2DPipe::getCoords(int ix, int iphi)
{
	glm::dvec3 coords;
	/*		x = r * cos(ang)
			y = r * sin(ang)	*/
	double rad = radInner + (double)ix * elsize.x;
	double phi = (double)iphi * dphi;

	coords.x = rad * glm::cos(phi);
	coords.y = rad * glm::sin(phi);
	coords += pos;
	return coords;
}