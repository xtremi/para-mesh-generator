#pragma once
#include "MeshSideRefinement.h"

class MeshCircularRefinement :
	public MeshSideRefinement
{
public:
	MeshCircularRefinement(const glm::dvec2& size, int _refRows, double _elSizeNorm, double	_elSizeRef);
	MeshCircularRefinement(const glm::dvec2& size, int _refRows, double _elSizeNorm, int	_refFactor);
};

