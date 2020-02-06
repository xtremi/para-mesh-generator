#pragma once
#include "Mesh3DCuboid.h"
#include "FeaWrite.h"
#include <vector>

class Mesh3DCube 
	: public Mesh3DCuboid
{
private:
	Mesh3DCube(const glm::dvec3& _pos, const glm::dvec3& _length);
public:
	Mesh3DCube(const glm::dvec3& _pos, const glm::dvec3& _length, const glm::ivec3& _nnodes);
	Mesh3DCube(const glm::dvec3& _pos, const glm::dvec3& _length, const glm::dvec3& _elsize);
	Mesh3DCube(const Mesh3DCube& rhs);

	glm::dvec3 getCoords(int ix, int iy, int iz);
	void writeNodes(std::ofstream& file, format_type format);
	void writeElements(std::ofstream& file, format_type format);

	int numberOfNodes();
	int numberOfElements();

	enum class face{
		face1, face2, face3, face4, face5, face6
	};
	enum class edge{ 
		edge12, edge23, edge34, edge41,
		edge56, edge67, edge78, edge85,
		edge15, edge26, edge37, edge48,

		edge21, edge32, edge43, edge14,
		edge65, edge76, edge87, edge58,
		edge51, edge62, edge73, edge84
	};
	enum class corner{ 
		corner1, corner2, corner3, corner4,
		corner5, corner6, corner7, corner8
	};
	std::vector<int> getEdgeNodeIds(edge edge_id, bool incrDirection = true);
	std::vector<int> getNextEdge();

	int getCornerNodeId(corner corner_id);
	int getEdgeStartNodeId(edge edge_id);
	int getNumberOfNodesOnEdge(edge edge_id);

	glm::dvec3 elsize;
	glm::ivec3 nnodes;

private:		
	bool isReversedEdge(edge edge_id);
	edge getReversedEdge(edge edge_id);
	int getEdgeIncrement(edge edge_id);
	int getMaxEdgeIterations(edge edge_id);
	
	std::vector<int> currentEdgeNodeIDs;
	edge	currentEdge;
	bool	edgeIsReversed			= false;
	int		edgeIncrmentor			= 0;
	int		maxEdgeIteration		= 0;
	int		currentEdgeIteration	= 0;
	bool	edgeIterationDir		= false;
};

int createElementsBetweenCubes(
	std::ofstream& file,
	Mesh3DCube* mc1, Mesh3DCube* mc2,
	Mesh3DCube::edge edg1, Mesh3DCube::edge edg2,
	bool dir1, bool dir2, int elStartID,
	format_type format);