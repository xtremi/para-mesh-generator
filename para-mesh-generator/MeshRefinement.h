#pragma once
#include "math_utilities.h"
#include "glm/glm.hpp"
#include "math.h"
#include "FEAwrite.h"

class MeshRefinement
{
protected:
	MeshRefinement();
protected:
	int		refFactor;
	double	elsizeRef;
	double	elsizeNorm;
	int		nRefinements = 0;

	virtual int writeRefinementNodes(FEAwriter* feaWriter, const glm::dvec3& spos, int nodeIDstart) = 0;
};

