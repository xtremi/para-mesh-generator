#pragma once
#include "Geometry.h"
class RectangularGeometry :
	public Geometry
{
public:
	RectangularGeometry(double _width, double _length) { width = _width; length = _length; }

private:
	double width;
	double length;

};

