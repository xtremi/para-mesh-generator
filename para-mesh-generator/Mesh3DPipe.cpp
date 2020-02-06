#pragma once
#include "Mesh3DPipe.h"

Mesh3DPipe::Mesh3DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, double _height, double _revAng)
	: Mesh3DTubular(_pos, _revAng < 0.0), PipeGeometry3D(_radInner, _radOuter, _height, _revAng)
{

}

/*
	elsize.x = size along radius
	elsize.y = size along inner edge
	elsize.z = size along height
*/
Mesh3DPipe::Mesh3DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, double _height, const glm::ivec3& _nnodes, double _revAng)
	: Mesh3DPipe(_pos, _radInner, _radOuter, _height, _revAng)
{
	nnodes = _nnodes;
	nnodes.y = nnodes.y - nnodes.y % 8;

	double l = radOuter - radInner;
	elsize.x = l / ((double)nnodes.x - 1.0);
	elsize.y = innerPerimeter / (double)nnodes.y;
	elsize.z = height / (double)nnodes.z;
	
	dphi = revAng / (double)nnodes.y;
}
Mesh3DPipe::Mesh3DPipe(const glm::dvec3& _pos, double _radInner, double _radOuter, double _height, const glm::dvec3& _elsize, double _revAng)
	: Mesh3DPipe(_pos, _radInner, _radOuter, _height, _revAng)
{
	elsize = _elsize;

	double l = radOuter - radInner;
	nnodes.x = (int)(l / elsize.x) + 1;
	nnodes.y = (int)(innerPerimeter / elsize.y);
	nnodes.z = (int)(height / elsize.z) + 1;

	nnodes.y -= nnodes.y % 8;

	elsize.x = l / ((double)nnodes.x - 1.0);
	elsize.y = innerPerimeter / (double)nnodes.y;
	elsize.z = height / (double)nnodes.z;

	dphi = revAng / (double)nnodes.y;

}

glm::dvec3 Mesh3DPipe::getCoords(int ix, int iphi, int iz) {

	glm::dvec3 coords;
	/*		x = r * cos(ang)
			y = r * sin(ang)	*/	
	double rad = radInner + (double)ix * elsize.x;
	double phi = (double)iphi * dphi;
	
	coords.x = rad * glm::cos(phi);
	coords.y = rad * glm::sin(phi);	
	coords.z = (double)iz * elsize.z;
	coords += pos;
	return coords;
}


