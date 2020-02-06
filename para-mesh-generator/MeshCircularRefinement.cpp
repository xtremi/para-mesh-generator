#include "MeshCircularRefinement.h"



MeshCircularRefinement::MeshCircularRefinement(const glm::dvec2& size, int _refRows, double _elSizeNorm, double	_elSizeRef)
	: MeshSideRefinement(size, _refRows, _elSizeNorm, _elSizeRef)
{

}
MeshCircularRefinement::MeshCircularRefinement(const glm::dvec2& size, int _refRows, double _elSizeNorm, int _refFactor)
	: MeshSideRefinement(size, _refRows, _elSizeNorm, _refFactor)
{

}
