#include "Mesh3D.h"

Mesh3D::Mesh3D(const glm::dvec3& _pos)
	: MeshPrimitive(_pos)
{
	_el_dim = element_dim_type::e3D;

}

