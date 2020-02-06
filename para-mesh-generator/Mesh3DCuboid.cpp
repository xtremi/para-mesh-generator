#include "Mesh3DCuboid.h"

Mesh3DCuboid::Mesh3DCuboid(const glm::dvec3& _pos, const glm::dvec3& _length)
	: Mesh3D(_pos)
{
	length = _length;
}


