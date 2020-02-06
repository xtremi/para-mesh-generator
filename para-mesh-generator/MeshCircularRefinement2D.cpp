#include "MeshCircularRefinement2D.h"



MeshCircularRefinement2D::MeshCircularRefinement2D(const glm::dvec2& size, int _refRows, double _elSizeNorm, double _elSizeRef)
	: MeshCircularRefinement(size, _refRows, _elSizeNorm, _elSizeRef)
{

}

MeshCircularRefinement2D::MeshCircularRefinement2D(const glm::dvec2& size, int _refRows, double _elSizeNorm, int _refFactor)
	: MeshCircularRefinement(size, _refRows, _elSizeNorm, _refFactor)
{

}