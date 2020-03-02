#pragma once
#include "Mesh2DRectangle.h"
#include "MeshSideRefinement2D.h"

class Mesh2DPlateRefSide :
	public Mesh2DRectangle, public MeshSideRefinement2D
{
public:
	Mesh2DPlateRefSide(const glm::dvec3& _pos, const glm::dvec2& _length, double _elsizeRef, double _elSizeNorm, int _refRows);
	Mesh2DPlateRefSide(const glm::dvec3& _pos, const glm::dvec2& _length, int    _refFactor, double _elSizeNorm, int _refRows);

	void writeNodes(FEAwriter* feaWriter);
	void writeElements(FEAwriter* feaWriter);

	int numberOfNodes();
	int numberOfElements();

private:
	int nodeID_endOfRefRows = 0;
	int nodeID_endOfRefinement = 0;

};

