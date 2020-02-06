#include "MeshCircularRefinement3D.h"



MeshCircularRefinement3D::MeshCircularRefinement3D(const glm::dvec3& size, int _refRows, double _elSizeNorm, double	_elSizeRef)
	:MeshSideRefinement3D(size, _refRows, _elSizeNorm, _elSizeRef)
{

}

MeshCircularRefinement3D::MeshCircularRefinement3D(const glm::dvec3& size, int _refRows, double _elSizeNorm, int	_refFactor)
	: MeshSideRefinement3D(size, _refRows, _elSizeNorm, _refFactor)
{

}