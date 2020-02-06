#pragma once
#include "Mesh3DElipsToRec.h"

Mesh3DElipsToRec::Mesh3DElipsToRec(const glm::dvec3& _pos, const glm::dvec2& _sqrdim, const glm::dvec2& _rad, double _height)
	: Mesh3DTubular(_pos, true)
{
	sqrdim = _sqrdim;
	rad		= _rad;
	height	= _height; 
	innerPerimeter = 2.0*(sqrdim.x + sqrdim.y);
	outerPerimeter = 2.0*M_PI * glm::sqrt(0.5*(glm::pow(rad.x, 2.0) + glm::pow(rad.y, 2.0)));
}

Mesh3DElipsToRec::Mesh3DElipsToRec(const glm::dvec3& _pos, const glm::dvec2& _sqrdim, const glm::dvec2& _rad, double _height, const glm::ivec3& _nnodes)
	: Mesh3DElipsToRec(_pos, _sqrdim, _rad, _height)
{
	nnodes = _nnodes;
	double lx = rad.x - sqrdim.x / 2.0;
	double ly = rad.y - sqrdim.y / 2.0;
	double l = glm::min(lx, ly);

	nnodesSx = (int)((sqrdim.x / innerPerimeter) * nnodes.y);
	nnodesSx -= nnodesSx % 2;
	nnodesSy = (nnodes.y - 2 * nnodesSx) / 2;
	nnodesSy -= nnodesSy % 2;
	nnodes.y = 2 * (nnodesSx + nnodesSy);

	elsize.x = l / ((double)nnodes.x - 1.0);
	elsize.y = innerPerimeter / (double)nnodes.y;
	elsize.z = height / (double)nnodes.z;

	dphi = 2.0*M_PI / (double)nnodes.y;
}


Mesh3DElipsToRec::Mesh3DElipsToRec(const glm::dvec3& _pos, const glm::dvec2& _sqrdim, const glm::dvec2& _rad, double _height, const glm::dvec3& _elsize)
	: Mesh3DElipsToRec(_pos, _sqrdim, _rad, _height)
{
	elsize = _elsize;
	double lx = abs(rad.x - sqrdim.x / 2.0);
	double ly = abs(rad.y - sqrdim.y / 2.0);
	double l = glm::min(lx, ly);

	nnodes.x = (int)(l / elsize.x) + 1;	
	nnodesSx = (int)(sqrdim.x / elsize.y);
	nnodesSx -= nnodesSx % 2;
	nnodesSy = (int)(sqrdim.y / elsize.y);
	nnodesSy -= nnodesSy % 2;
	nnodes.y = 2 * (nnodesSx + nnodesSy);
	nnodes.z = (int)(height / elsize.z) + 1;


	elsize.x = l / ((double)nnodes.x - 1.0);
	elsize.y = innerPerimeter / (double)nnodes.y;
	elsize.z = height / (double)nnodes.z;

	dphi = 2.0*M_PI / (double)nnodes.y;
}
/*
nnodesSy = 6
nnodesSx = 8
nnodes.y = 2*(6 + 8) = 28

  (s2)
   11       | 6 5 4     
    # x x x x x x x #  3 (s1) 
	x       |       x  2
 	x       |       x  1
	x       |-------x  0
	x               x  27
	x               x  26
	# x x x x x x x #  25 (s4)
   17          
  (s3)
*/
glm::dvec3 Mesh3DElipsToRec::getCoords(int ir, int iphi, int iz)
{
	const int s1 = nnodesSy / 2;
	const int s2 = s1 + nnodesSx;
	const int s3 = s2 + nnodesSy;
	const int s4 = s3 + nnodesSx;
	const double sx = sqrdim.x / 2.0;
	const double sy = sqrdim.y / 2.0;

	double phi = (double)iphi * dphi;

	glm::dvec3 coords;
	glm::dvec2 c1, c2;
	c2 = glm::dvec2(rad.x*glm::cos(phi), rad.y*glm::sin(phi));

	if (iphi <= s1 || iphi > s4) {
		c1.x = sx;
		if (iphi <= s1)
			c1.y = (iphi + s1) * elsize.y - sy;
		else
			c1.y = (iphi - s4)* elsize.y - sy;
	}
	else if(iphi > s3){
		c1.x = (iphi - s3) * elsize.y - sx;
		c1.y = -sy;
	}
	else if (iphi > s2) {
		c1.x = -sx;
		c1.y = sy - (iphi - s2) * elsize.y;
	}
	else if (iphi > s1) {
		c1.x = sx - (iphi - s1) * elsize.y;
		c1.y = sy;
	}

	
	glm::dvec2 dc = c2 - c1;
	double L = glm::length(dc);
	dc = glm::normalize(dc);

	coords = glm::dvec3(c1 + dc * L * (double)ir / (double)(nnodes.x - 1), 0.0);
	coords.z = iz * elsize.z;

	return coords;
}
