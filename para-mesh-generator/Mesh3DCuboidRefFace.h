#pragma once
#include "Mesh3DCuboid.h"
#include "MeshSideRefinement3D.h"

class Mesh3DCuboidRefFace :
	public Mesh3DCuboid, public MeshSideRefinement3D
{
public:
	Mesh3DCuboidRefFace(const glm::dvec3& _pos, const glm::dvec3& _length, double _elsizeRef, double _elSizeNorm, int _refRows);
	Mesh3DCuboidRefFace(const glm::dvec3& _pos, const glm::dvec3& _length, int    _refFactor, double _elSizeNorm, int _refRows);

	void writeNodes(std::ofstream& file, format_type format);
	void writeElements(std::ofstream& file, format_type format);

	int numberOfNodes();
	int numberOfElements();

	int nodeID_endOfRefRows;
	int nodeID_endOfRefinement;

};

