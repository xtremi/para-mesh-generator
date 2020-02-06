#pragma once
#include "Mesh2D.h"
class Mesh2DRectangle 
	:	public Mesh2D
{
public:
	Mesh2DRectangle(const glm::dvec3& pos, const glm::dvec2& _length);

protected:
	glm::dvec2 length;

};

