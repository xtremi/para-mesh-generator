#pragma once
#include "PipeGeometry2D.h"
class PipeGeometry3D :
	public PipeGeometry2D
{
public:
	PipeGeometry3D(double _radInner, double _radOuter, double _height, double _revAng);
	

protected:
	double height;
};

