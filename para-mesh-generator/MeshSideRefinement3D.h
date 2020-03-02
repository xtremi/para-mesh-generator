#pragma once
#include "MeshCircularRefinement.h"
class MeshSideRefinement3D :
	public MeshCircularRefinement
{
public:
	MeshSideRefinement3D(const glm::dvec3& size, int _refRows, double _elSizeNorm, double	_elSizeRef);
	MeshSideRefinement3D(const glm::dvec3& size, int _refRows, double _elSizeNorm, int	_refFactor);

protected:
	int	    nnodesRefZ;
	int	    nnodesNormZ;
	double	elsizeRefZ;
	double	elsizeNormZ;

	void calculateMeshSectionRefToNormLength();
	void normZelementSizeAndNumbersFromRefFactor(double lengthz);
	void correctRefZElementSizeAndNumbers(double lengthz);
	
	int writeRefinementNodes(FEAwriter* feaWriter, const glm::dvec3& spos, int nodeIDstart);
	int writeRefinementElements(FEAwriter* feaWriter, int elementID1, int nodeID1);
};

