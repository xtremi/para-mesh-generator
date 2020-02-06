#include "Mesh2DRectangle.h"

Mesh2DRectangle::Mesh2DRectangle(const glm::dvec3& _pos, const glm::dvec2& _length)
	: Mesh2D(_pos)
{
	length = _length;
}

