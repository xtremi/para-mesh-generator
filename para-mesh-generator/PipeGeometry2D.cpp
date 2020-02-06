#include "PipeGeometry2D.h"

PipeGeometry2D::PipeGeometry2D(double _radInner, double _radOuter, double _revAng)
{
	radInner = _radInner;
	radOuter = _radOuter;

	if (_revAng > 0.0) {
		completeRev = false;
		revAng = _revAng;
	}
	else
		revAng = 2.0 * M_PI;

	innerPerimeter = revAng * radInner;
	outerPerimeter = revAng * radOuter;
}


