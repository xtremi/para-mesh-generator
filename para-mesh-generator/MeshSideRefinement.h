#pragma once
#include "MeshRefinement.h"

class MeshSideRefinement :
	public MeshRefinement
{
public:
	MeshSideRefinement(const glm::dvec2& size, int _refRows, double _elSizeNorm, double	_elSizeRef);
	MeshSideRefinement(const glm::dvec2& size, int _refRows, double _elSizeNorm, int	_refFactor);

protected:
	double  elsizeNormY;
	int		nnodesRef;
	int		nnodesNorm;

	int		normRows;
	int		refRows;
	
	double  l_ref;
	double  l_norm;
	double  l_ref_to_norm;

	double yfac = 1.0;

	void correctNormElementSizeAndNumbers(double lengthx);
	void correctRefElementSizeAndNumbers(double lengthx);
	void correctRefFactor();
	void normElementSizeAndNumbersFromRefFactor(double lengthx);
	void calculateMeshSectionLengths(double lengthy);
	virtual void calculateMeshSectionRefToNormLength();
};

