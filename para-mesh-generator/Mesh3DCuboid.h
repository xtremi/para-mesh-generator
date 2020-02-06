#pragma once
#include "Mesh3D.h"

class Mesh3DCuboid
	: public Mesh3D
{
public:
	Mesh3DCuboid(const glm::dvec3& _pos, const glm::dvec3& _length);
protected:
	glm::dvec3 length;
};

