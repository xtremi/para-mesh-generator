#pragma once
#include "Mesh3D.h"
class Mesh3DTubular :
	public Mesh3D
{
public:
	Mesh3DTubular(const glm::dvec3& _pos, bool _completeRev);

	virtual glm::dvec3 getCoords(int ir, int iy, int iz) = 0;
	void writeNodes(std::ofstream& file, format_type format);
	void writeElements(std::ofstream& file, format_type format);
	int numberOfNodes();
	int numberOfElements();
	
	double elsizex() { return elsize.x; }
	double elsizey() { return elsize.y; }
	double elsizez() { return elsize.z; }

	int nnodesx() { return nnodes.x; }
	int nnodesy() { return nnodes.y; }
	int nnodesz() { return nnodes.z; }

	glm::ivec3 getNnodes() { return nnodes; }
	glm::dvec3 getElsize() { return elsize; }

	enum class edge {
		edge_inner_z, edge_outer_z
	};
	std::vector<int> getEdgeNodeIds(edge edge_id);
	std::vector<int> getNextEdge();

	bool hasCompleteRevolution() { return completeRev; }

protected:
	glm::ivec3 nnodes;
	glm::dvec3 elsize;
	bool completeRev = true;

	std::vector<int> currentEdgeNodeIDs;
	edge	currentEdge;
	int		maxEdgeIteration = 0;
	int		currentEdgeIteration = 0;
};

int createElementsBetweenTube(
	std::ofstream&	file,
	Mesh3DTubular*		tubeOuter, 
	Mesh3DTubular*		tubeInner,
	int				elStartID,
	format_type		format);