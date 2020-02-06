#pragma once
#include "Geometry.h"
class PipeGeometry2D :
	public Geometry
{
public:
	PipeGeometry2D(double _radInner, double _radOuter, double _revAng);	

	bool hasCompleteRevolution() { return completeRev; }

protected:
	double radInner, radOuter;

	double dphi = 0.0;
	double innerPerimeter = 0.0;
	double outerPerimeter = 0.0;

	bool completeRev = true;
	double revAng = -1.0;

};

