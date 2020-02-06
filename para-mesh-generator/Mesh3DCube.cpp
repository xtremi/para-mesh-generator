#pragma once
#include "Mesh3DCube.h"

Mesh3DCube::Mesh3DCube(const glm::dvec3& _pos, const glm::dvec3& _length) 
	: Mesh3DCuboid(_pos, _length)
{
}

Mesh3DCube::Mesh3DCube(const glm::dvec3& _pos, const glm::dvec3& _length, const glm::ivec3& _nnodes) 
	: Mesh3DCube(_pos, _length) {
	nnodes = _nnodes;

	elsize = length / (glm::dvec3)(nnodes - glm::ivec3(1));
}

Mesh3DCube::Mesh3DCube(const glm::dvec3& _pos, const glm::dvec3& _length, const glm::dvec3& _elsize) 
	: Mesh3DCube(_pos, _length) {
	elsize = _elsize;

	nnodes = (glm::ivec3)(length / elsize) + glm::ivec3(1);
	elsize = length / (glm::dvec3)(nnodes - glm::ivec3(1));
}

Mesh3DCube::Mesh3DCube(const Mesh3DCube& rhs) 
	: Mesh3DCuboid(rhs.pos, rhs.length) 
{
	this->nnodes = rhs.nnodes;
	this->elsize = rhs.elsize;
}


glm::dvec3 Mesh3DCube::getCoords(int ix, int iy, int iz) {
	glm::dvec3 coords = pos + glm::dvec3(ix, iy, iz) * elsize;
	return coords;
}



void Mesh3DCube::writeNodes(std::ofstream& file, format_type format) {
	int nodeID = nodeID1;
	for (int iz = 0; iz < nnodes.z; iz++) {
		for (int iy = 0; iy < nnodes.y; iy++) {
			for (int ix = 0; ix < nnodes.x; ix++) {
				writeNode(file, nodeID++, getCoords(ix, iy, iz), format);
			}
		}
	}
}

void Mesh3DCube::writeElements(std::ofstream& file, format_type format) {
	int n[8];
	int c = nodeID1;
	int nNodesXYface = nnodes.x * nnodes.y;
	int elID = elementID1;
	bool stop = false;
	for (int iz = 0; iz < (nnodes.z - 1); iz++) {
		for (int iy = 0; iy < (nnodes.y - 1); iy++) {
			for (int ix = 0; ix < (nnodes.x - 1); ix++) {

				n[0] = c + nNodesXYface;
				n[1] = n[0] + 1;
				n[2] = c + 1;
				n[3] = c;
				n[4] = n[0] + nnodes.x;
				n[5] = n[4] + 1;
				n[6] = n[5] - nNodesXYface;
				n[7] = n[6] - 1;

				c++;
				write8nodedHexa(file, elID++, n, format);

				if (false && (elID > (3 * 16 * 5))) {
					stop = true;
					break;
				}

			}
			c++;
			if (stop) break;
		}
		c += nnodes.x;
		if (stop) break;
	}
}



int Mesh3DCube::numberOfNodes() { 
	return nnodes.x*nnodes.y*nnodes.z;
}
int Mesh3DCube::numberOfElements() {
	return (nnodes.x - 1) * (nnodes.y - 1) * (nnodes.z - 1);
}

/*

8
@ + + + + + + + + + + + @ 7
+\                      +\
+ \                     + \
+  \                    +  \
+   \ 5                 +   \ 6
+    @ + + + + + + + + +++ + @
+    +                  +    +
+    +                  +    +
+    +                  +    +
+    +                  +    +
+    +                  +    +
+ 4  +                  +    +
@ + +++ + + + + + + + + @ 3  +
 \   +                   \   +
  \  +                    \  +
   \ +                     \ +
	\+                      \+
	 @ + + + + + + + + + + + @
	 1                       2

*/
std::vector<int> Mesh3DCube::getEdgeNodeIds(edge edge_id, bool incrDirection)
{
	currentEdgeIteration = 0;
	currentEdgeNodeIDs.clear();
	currentEdge = edge_id;
	edgeIterationDir = incrDirection;

	edgeIsReversed = isReversedEdge(edge_id);
	if (edgeIsReversed)
		edge_id = getReversedEdge(edge_id);

	int id		= getEdgeStartNodeId(edge_id);
	int nNodes	= getNumberOfNodesOnEdge(edge_id);

	int idIncr = 0;
	switch (edge_id)
	{
	case Mesh3DCube::edge::edge12: 
	case Mesh3DCube::edge::edge56: idIncr = -1; break;
	case Mesh3DCube::edge::edge23: 
	case Mesh3DCube::edge::edge67: idIncr = nnodes.x * nnodes.y; break;
	case Mesh3DCube::edge::edge34: 
	case Mesh3DCube::edge::edge78: idIncr = 1; break;
	case Mesh3DCube::edge::edge41: 
	case Mesh3DCube::edge::edge85: idIncr = -nnodes.x * nnodes.y; break;
	case Mesh3DCube::edge::edge15: 
	case Mesh3DCube::edge::edge26: 
	case Mesh3DCube::edge::edge37:
	case Mesh3DCube::edge::edge48: idIncr = nnodes.x; break;
	default:
		idIncr = -1; break;
	}
	
	for(int i = 0; i < nNodes; i++)
	{
		currentEdgeNodeIDs.push_back(id);
		id += idIncr;
	}	

	if (edgeIsReversed) {
		std::reverse(currentEdgeNodeIDs.begin(), currentEdgeNodeIDs.end());
	}

	edgeIncrmentor			= getEdgeIncrement(edge_id);
	maxEdgeIteration		= getMaxEdgeIterations(edge_id);
	currentEdgeIteration	= 1;

	return currentEdgeNodeIDs;
}

std::vector<int> Mesh3DCube::getNextEdge() 
{
	if (currentEdgeIteration >= maxEdgeIteration)
		return std::vector<int>();

	for (int& id : currentEdgeNodeIDs)
		id += edgeIncrmentor;

	currentEdgeIteration++;
	return currentEdgeNodeIDs;
}

int Mesh3DCube::getMaxEdgeIterations(edge edge_id) {
	switch (edge_id)
	{
	case Mesh3DCube::edge::edge12: case Mesh3DCube::edge::edge21:
	case Mesh3DCube::edge::edge34: case Mesh3DCube::edge::edge32:
		return edgeIterationDir ? nnodes.y : nnodes.z;
		break;
	case Mesh3DCube::edge::edge23: case Mesh3DCube::edge::edge43:
	case Mesh3DCube::edge::edge41: case Mesh3DCube::edge::edge14:
		return edgeIterationDir ? nnodes.y : nnodes.x;

	case Mesh3DCube::edge::edge56: case Mesh3DCube::edge::edge65:
	case Mesh3DCube::edge::edge78: case Mesh3DCube::edge::edge87:
		return edgeIterationDir ? nnodes.z : nnodes.y;

	case Mesh3DCube::edge::edge67: case Mesh3DCube::edge::edge76:	
	case Mesh3DCube::edge::edge85: case Mesh3DCube::edge::edge58:
		return edgeIterationDir ? nnodes.x : nnodes.y;

	case Mesh3DCube::edge::edge15: case Mesh3DCube::edge::edge51:
	case Mesh3DCube::edge::edge37: case Mesh3DCube::edge::edge73:
		return edgeIterationDir ? nnodes.z : nnodes.x; break;

	case Mesh3DCube::edge::edge26: case Mesh3DCube::edge::edge62:
	case Mesh3DCube::edge::edge48: case Mesh3DCube::edge::edge84:
		return edgeIterationDir ? nnodes.x : nnodes.z; break;
	
	default:
		return 0; break;
	}

}
int Mesh3DCube::getEdgeIncrement(edge edge_id) {

	switch (edge_id)
	{
	case Mesh3DCube::edge::edge12: case Mesh3DCube::edge::edge21:
		return edgeIterationDir ? nnodes.x : nnodes.x * nnodes.y;
	case Mesh3DCube::edge::edge23: case Mesh3DCube::edge::edge32:
		return edgeIterationDir ? nnodes.x : 1; break;
	case Mesh3DCube::edge::edge34: case Mesh3DCube::edge::edge43:
		return edgeIterationDir ? nnodes.x : -nnodes.x * nnodes.y; break;
	case Mesh3DCube::edge::edge41: case Mesh3DCube::edge::edge14:
		return edgeIterationDir ? nnodes.x : -1; break;
	
	case Mesh3DCube::edge::edge56: case Mesh3DCube::edge::edge65:
		return edgeIterationDir ? nnodes.x * nnodes.y : -nnodes.x; break;
	case Mesh3DCube::edge::edge67: case Mesh3DCube::edge::edge76:
		return edgeIterationDir ? 1 : -nnodes.x; break;
	case Mesh3DCube::edge::edge78: case Mesh3DCube::edge::edge87:
		return edgeIterationDir ? -nnodes.x * nnodes.y : -nnodes.x; break;
	case Mesh3DCube::edge::edge85: case Mesh3DCube::edge::edge58:
		return edgeIterationDir ? -1 : -nnodes.x; break;

	case Mesh3DCube::edge::edge15: case Mesh3DCube::edge::edge51:
		return edgeIterationDir ? nnodes.x*nnodes.y : -1; break;
	case Mesh3DCube::edge::edge26: case Mesh3DCube::edge::edge62:
		return edgeIterationDir ? 1 : nnodes.x*nnodes.y; break;
	case Mesh3DCube::edge::edge37: case Mesh3DCube::edge::edge73:
		return edgeIterationDir ? -nnodes.x*nnodes.y : 1; break;
	case Mesh3DCube::edge::edge48: case Mesh3DCube::edge::edge84:
		return edgeIterationDir ? -1 : -nnodes.x*nnodes.y; break;

	default:
		return 0; break;
	}

}

Mesh3DCube::edge Mesh3DCube::getReversedEdge(edge edge_id) {
	switch (edge_id)
	{
	case Mesh3DCube::edge::edge12: return Mesh3DCube::edge::edge21; break;
	case Mesh3DCube::edge::edge23: return Mesh3DCube::edge::edge32; break;
	case Mesh3DCube::edge::edge34: return Mesh3DCube::edge::edge43; break;
	case Mesh3DCube::edge::edge41: return Mesh3DCube::edge::edge41; break;
	case Mesh3DCube::edge::edge56: return Mesh3DCube::edge::edge65; break;
	case Mesh3DCube::edge::edge67: return Mesh3DCube::edge::edge76; break;
	case Mesh3DCube::edge::edge78: return Mesh3DCube::edge::edge87; break;
	case Mesh3DCube::edge::edge85: return Mesh3DCube::edge::edge58; break;
	case Mesh3DCube::edge::edge15: return Mesh3DCube::edge::edge51; break;
	case Mesh3DCube::edge::edge26: return Mesh3DCube::edge::edge62; break;
	case Mesh3DCube::edge::edge37: return Mesh3DCube::edge::edge73; break;
	case Mesh3DCube::edge::edge48: return Mesh3DCube::edge::edge84; break;

	case Mesh3DCube::edge::edge21: return Mesh3DCube::edge::edge12; break;
	case Mesh3DCube::edge::edge32: return Mesh3DCube::edge::edge23; break;
	case Mesh3DCube::edge::edge43: return Mesh3DCube::edge::edge34; break;
	case Mesh3DCube::edge::edge14: return Mesh3DCube::edge::edge41; break;
	case Mesh3DCube::edge::edge65: return Mesh3DCube::edge::edge56; break;
	case Mesh3DCube::edge::edge76: return Mesh3DCube::edge::edge67; break;
	case Mesh3DCube::edge::edge87: return Mesh3DCube::edge::edge78; break;
	case Mesh3DCube::edge::edge58: return Mesh3DCube::edge::edge85; break;
	case Mesh3DCube::edge::edge51: return Mesh3DCube::edge::edge15; break;
	case Mesh3DCube::edge::edge62: return Mesh3DCube::edge::edge26; break;
	case Mesh3DCube::edge::edge73: return Mesh3DCube::edge::edge37; break;
	case Mesh3DCube::edge::edge84: return Mesh3DCube::edge::edge48; break;
	default:
		return Mesh3DCube::edge::edge12;
		break;
	}
}

bool Mesh3DCube::isReversedEdge(edge edge_id) {
	switch (edge_id)
	{
	case Mesh3DCube::edge::edge21:
	case Mesh3DCube::edge::edge32:
	case Mesh3DCube::edge::edge43:
	case Mesh3DCube::edge::edge14:
	case Mesh3DCube::edge::edge65:
	case Mesh3DCube::edge::edge76:
	case Mesh3DCube::edge::edge87:
	case Mesh3DCube::edge::edge58:
	case Mesh3DCube::edge::edge51:
	case Mesh3DCube::edge::edge62:
	case Mesh3DCube::edge::edge73:
	case Mesh3DCube::edge::edge84:
		return true;
		break;
	default:
		return false;
		break;
	}
}


int Mesh3DCube::getNumberOfNodesOnEdge(edge edge_id) {
	switch (edge_id)
	{
	case Mesh3DCube::edge::edge12:
	case Mesh3DCube::edge::edge34:
	case Mesh3DCube::edge::edge56:
	case Mesh3DCube::edge::edge78:
		return nnodes.x;
		break;
	case Mesh3DCube::edge::edge23:
	case Mesh3DCube::edge::edge41:
	case Mesh3DCube::edge::edge67:
	case Mesh3DCube::edge::edge85:
		return nnodes.z;
		break;
	case Mesh3DCube::edge::edge15:
	case Mesh3DCube::edge::edge26:
	case Mesh3DCube::edge::edge37:
	case Mesh3DCube::edge::edge48:
		return nnodes.y;
		break;
	default:
		return -1;
		break;
	}

}

int Mesh3DCube::getEdgeStartNodeId(edge edge_id) {

	switch (edge_id)
	{
	case Mesh3DCube::edge::edge12:
	case Mesh3DCube::edge::edge15:
		return getCornerNodeId(corner::corner1);	break;
	case Mesh3DCube::edge::edge23:
	case Mesh3DCube::edge::edge26:
		return getCornerNodeId(corner::corner2);	break;
	case Mesh3DCube::edge::edge34:
	case Mesh3DCube::edge::edge37:
		return getCornerNodeId(corner::corner3);	break;
	case Mesh3DCube::edge::edge41:
	case Mesh3DCube::edge::edge48:
		return getCornerNodeId(corner::corner4);	break;
	case Mesh3DCube::edge::edge56:
		return getCornerNodeId(corner::corner5);	break;
	case Mesh3DCube::edge::edge67:
		return getCornerNodeId(corner::corner6);	break;
	case Mesh3DCube::edge::edge78:
		return getCornerNodeId(corner::corner7);	break;
	case Mesh3DCube::edge::edge85:
		return getCornerNodeId(corner::corner8);	break;
	default:
		return -1;
		break;
	}
}

int Mesh3DCube::getCornerNodeId(corner corner_id) {

	switch (corner_id)
	{
	case Mesh3DCube::corner::corner1:
		return nodeID1 + nnodes.x - 1;
		break;
	case Mesh3DCube::corner::corner2:
		return nodeID1;
		break;
	case Mesh3DCube::corner::corner3:
		return nodeID1 + nnodes.x * nnodes.y * (nnodes.z - 1);
		break;
	case Mesh3DCube::corner::corner4:
		return nodeID1 + nnodes.x * nnodes.y * (nnodes.z - 1) + nnodes.x - 1;
		break;
	case Mesh3DCube::corner::corner5:
		return nodeID1 + nnodes.x * nnodes.y - 1;
		break;
	case Mesh3DCube::corner::corner6:
		return nodeID1 + nnodes.x * (nnodes.y - 1);
		break;
	case Mesh3DCube::corner::corner7:
		return nodeID1 + numberOfNodes() - nnodes.x;
		break;
	case Mesh3DCube::corner::corner8:
		return nodeID1 + numberOfNodes() - 1;
		break;
	default:
		return -1;
		break;
	}

}



int createElementsBetweenCubes(
	std::ofstream& file,
	Mesh3DCube* mc1, Mesh3DCube* mc2,
	Mesh3DCube::edge edg1, Mesh3DCube::edge edg2,
	bool dir1, bool dir2, int elStartID,
	format_type format)
{
	std::vector<int> edge1 = mc1->getEdgeNodeIds(edg1, dir1);
	std::vector<int> edge2 = mc2->getEdgeNodeIds(edg2, dir2);
	std::vector<int> nextEdge1 = mc1->getNextEdge();
	std::vector<int> nextEdge2 = mc2->getNextEdge();

	int elID = elStartID;
	while ((nextEdge1.size() > 0) && (nextEdge2.size() > 0))
	{
		elID = writeElementRow(file, format, edge2, edge1, nextEdge1, nextEdge2, elID);

		edge1 = nextEdge1;
		edge2 = nextEdge2;
		nextEdge1 = mc1->getNextEdge();
		nextEdge2 = mc2->getNextEdge();
	}

	return elID;
}