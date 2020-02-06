#pragma once
#include "MeshCircularRefinement.h"
class MeshCircularRefinement2D :
	public MeshCircularRefinement
{
public:
	MeshCircularRefinement2D(const glm::dvec2& size, int _refRows, double _elSizeNorm, double _elSizeRef);
	MeshCircularRefinement2D(const glm::dvec2& size, int _refRows, double _elSizeNorm, int _refFactor);
};

