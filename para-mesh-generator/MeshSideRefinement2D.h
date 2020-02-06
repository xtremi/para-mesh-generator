#pragma once
#include "MeshSideRefinement.h"
class MeshSideRefinement2D :
	public MeshSideRefinement
{
public:
	MeshSideRefinement2D(const glm::dvec2& size, int _refRows, double _elSizeNorm, double	_elSizeRef);
	MeshSideRefinement2D(const glm::dvec2& size, int _refRows, double _elSizeNorm, int	_refFactor);

protected:
	int writeRefinementNodes(std::ofstream& file, format_type format, const glm::dvec3& spos, int nodeIDstart);
	int writeRefinementElements(std::ofstream& file, format_type format, int elementID1, int nodeID1);

};

