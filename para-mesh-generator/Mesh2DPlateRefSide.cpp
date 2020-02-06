#pragma once
#include "Mesh2DPlateRefSide.h"
/*

_________________                ___
                                  |
   not refined (elsizeNorm)       |   L-norm  
                                  |
_________________                _|_
                                  |  
   refinement from ref to norm    |   L-mid
                                  |
_________________                _|_
                                  |
  refined (elsizeRef)             |   L-ref
_________________                _|_

*/

Mesh2DPlateRefSide::Mesh2DPlateRefSide(
	const glm::dvec3&	_pos, 
	const glm::dvec2&	_length, 
	int					_refFactor, 
	double				_elSizeNorm, 
	int					_refRows
) 
	: Mesh2DRectangle(_pos, _length), MeshSideRefinement2D(_length, _refRows, _elSizeNorm, _refFactor)
{}

Mesh2DPlateRefSide::Mesh2DPlateRefSide(
	const glm::dvec3&	_pos, 
	const glm::dvec2&	_length, 
	double				_elsizeRef,
	double				_elsizeNorm, 
	int					_refRows
)
	: Mesh2DRectangle(_pos, _length), MeshSideRefinement2D(_length, _refRows, _elsizeRef, _elsizeNorm)
{}

/*     

	 x_______x_______x_______x_______x
	 |       |       |       |       |
	 |       |       |       |       |
t0   x_______x_______x_______x_______x  row t (top)
	 | \     |     / |  \    |     / |  elRow t
	 |m0 x___x___x	 |   x___x___x	 |  row m (mid)
	 |   |   |   |   |   |   |   |   |	elRow m
b0   x___x___x___x___x___x___x___x___x  row b (bot)
	 |   |   |   |   |   |   |   |   |	elRow b
	 x___x___x___x___x___x___x___x___x ref2
	 |   |   |   |   |   |   |   |   |
	 x___x___x___x___x___x___x___x___x ref1

*/

void Mesh2DPlateRefSide::writeNodes(std::ofstream& file, format_type format) {
	glm::dvec3 coords(pos);
	nodeID_endOfRefRows = writeNodePlaneXY(file, format, coords , glm::dvec2(elsizeRef), glm::ivec2(nnodesRef, refRows), nodeID1);
	coords.y = (l_ref + elsizeRef*yfac);
	nodeID_endOfRefinement = writeRefinementNodes(file, format, coords, nodeID_endOfRefRows);
	coords.y = (l_ref + l_ref_to_norm + elsizeNormY);
	writeNodePlaneXY(file, format, coords, glm::dvec2(elsizeNorm, elsizeNormY), glm::ivec2(nnodesNorm, normRows), nodeID_endOfRefinement);
}

void Mesh2DPlateRefSide::writeElements(std::ofstream& file, format_type format) {
	int nodeID = nodeID1;
	int elID = writeElementsPlaneXY(file, format, glm::ivec2(nnodesRef, refRows), nodeID, elementID1);
	
	nodeID = nodeID_endOfRefRows - nnodesRef;
	elID = writeRefinementElements(file, format, elID, nodeID);

	nodeID = nodeID_endOfRefinement - nnodesNorm;
	writeElementsPlaneXY(file, format, glm::ivec2(nnodesNorm, normRows), nodeID, elID);
}

int Mesh2DPlateRefSide::numberOfNodes() {
	return 0;
}
int Mesh2DPlateRefSide::numberOfElements() {
	return 0;
}


