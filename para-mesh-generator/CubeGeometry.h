#pragma once
#include "RectangularGeometry.h"
class CubeGeometry :
	public RectangularGeometry
{
public:
	CubeGeometry(double _width, double _length, double _depth)
		: RectangularGeometry(_width, _length)
	{
		depth = _depth;
	}

private:
	double depth;
};

