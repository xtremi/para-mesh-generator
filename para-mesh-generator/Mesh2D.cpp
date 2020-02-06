#include "Mesh2D.h"

Mesh2D::Mesh2D(const glm::dvec3& _pos)
	: MeshPrimitive(_pos)
{
	_el_dim = element_dim_type::e2D;
}

