#include "PipeGeometry3D.h"

PipeGeometry3D::PipeGeometry3D(double _radInner, double _radOuter, double _height, double _revAng)
	: PipeGeometry2D(_radInner, _radOuter, _revAng)
{
	height = _height;
}
