#pragma once
#include "math_utilities.h"
#include "glm/glm.hpp"
#include "math.h"
#include "MeshWrite.h"

class MeshRefinement
{
protected:
	MeshRefinement();
protected:
	int		refFactor;
	double	elsizeRef;
	double	elsizeNorm;
	int		nRefinements = 0;

	virtual int writeRefinementNodes(std::ofstream& file, format_type format, const glm::dvec3& spos, int nodeIDstart) = 0;
};

