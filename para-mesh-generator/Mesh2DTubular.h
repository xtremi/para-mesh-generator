#pragma once
#include "Mesh2D.h"
class Mesh2DTubular :
	public Mesh2D
{
public:
	Mesh2DTubular(const glm::dvec3& _pos, bool _completeRev);

	virtual glm::dvec3 getCoords(int ir, int iy) = 0;
	void writeNodes(std::ofstream& file, format_type format);
	void writeElements(std::ofstream& file, format_type format);
	int numberOfNodes();
	int numberOfElements();

	double elsizex() { return elsize.x; }
	double elsizey() { return elsize.y; }

	int nnodesx() { return nnodes.x; }
	int nnodesy() { return nnodes.y; }

	glm::ivec2 getNnodes() { return nnodes; }
	glm::dvec2 getElsize() { return elsize; }

	enum class edge {
		edge_inner_z, edge_outer_z
	};

	std::vector<int> getEdgeNodeIds(edge edge_id);
	std::vector<int> getNextEdge();

	

protected:
	glm::ivec2 nnodes;
	glm::dvec2 elsize;
	bool completeRev = true;

	std::vector<int> currentEdgeNodeIDs;
	edge	currentEdge;
	int		maxEdgeIteration = 0;
	int		currentEdgeIteration = 0;

};

