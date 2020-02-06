#pragma once
#include "MeshSideRefinement3D.h"
class MeshCircularRefinement3D :
	public MeshSideRefinement3D
{
public:
	MeshCircularRefinement3D(const glm::dvec3& size, int _refRows, double _elSizeNorm, double	_elSizeRef);
	MeshCircularRefinement3D(const glm::dvec3& size, int _refRows, double _elSizeNorm, int	_refFactor);
	



};

