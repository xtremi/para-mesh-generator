#include "Mesh3DCuboidRefFace.h"



Mesh3DCuboidRefFace::Mesh3DCuboidRefFace(
	const glm::dvec3&	_pos,
	const glm::dvec3&	_length,
	double				_elSizeRef,
	double 				_elSizeNorm,
	int					_refRows
)
	: Mesh3DCuboid(_pos, _length), MeshSideRefinement3D(_length, _refRows, _elSizeNorm, _elSizeRef)
{}

Mesh3DCuboidRefFace::Mesh3DCuboidRefFace(
	const glm::dvec3&	_pos,
	const glm::dvec3&	_length,
	int					_refFactor,
	double				_elSizeNorm,
	int					_refRows
)
	: Mesh3DCuboid(_pos, _length), MeshSideRefinement3D(_length, _refRows, _elSizeNorm, _refFactor)
{}


void Mesh3DCuboidRefFace::writeNodes(FEAwriter* feaWriter){
	glm::dvec3 coords(pos);
	nodeID_endOfRefRows = feaWriter->writeNodeCuboidXZY(coords, glm::dvec3(elsizeRef, elsizeRef, elsizeRefZ), glm::ivec3(nnodesRef, refRows, nnodesRefZ), nodeID1);
	coords.y = (l_ref + elsizeRef * yfac);
	nodeID_endOfRefinement = writeRefinementNodes(feaWriter, coords, nodeID_endOfRefRows);
	coords.y = (l_ref + l_ref_to_norm + elsizeNormY);
	feaWriter->writeNodeCuboidXZY(coords, glm::dvec3(elsizeNorm, elsizeNormY, elsizeNormZ), glm::ivec3(nnodesNorm, normRows, nnodesNormZ), nodeID_endOfRefinement);
}
void Mesh3DCuboidRefFace::writeElements(FEAwriter* feaWriter) {
	int elementID = elementID1;
	elementID = feaWriter->writeElementsCubeXZY(glm::ivec3(nnodesRef, refRows, nnodesRefZ), nodeID1, elementID);
	elementID = writeRefinementElements(feaWriter, elementID, nodeID_endOfRefRows - nnodesRef * nnodesRefZ);
	//adding a row of elements between refinement rows and norm rows:
	elementID = feaWriter->writeElementsCubeXZY(glm::ivec3(nnodesNorm, normRows + 1, nnodesNormZ), nodeID_endOfRefinement - nnodesNorm*nnodesNormZ, elementID);
}

int Mesh3DCuboidRefFace::numberOfNodes() { return 0; }
int Mesh3DCuboidRefFace::numberOfElements() { return 0; }