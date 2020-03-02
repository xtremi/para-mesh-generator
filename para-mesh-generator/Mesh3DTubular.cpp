#include "Mesh3DTubular.h"

Mesh3DTubular::Mesh3DTubular(const glm::dvec3& _pos, bool _completeRev)
	: Mesh3D(_pos)
{
	completeRev = _completeRev;
}


void Mesh3DTubular::writeNodes(FEAwriter* feaWriter){
	int nodeID = nodeID1;
	for (int iz = 0; iz < nnodes.z; iz++) {
		for (int ix = 0; ix < nnodes.x; ix++) {
			for (int iphi = 0; iphi < nnodes.y; iphi++) {
				glm::dvec3 c = getCoords(ix, iphi, iz);
				feaWriter->writeNode(nodeID++, c);
			}
		}
	}
}
void Mesh3DTubular::writeElements(FEAwriter* feaWriter) {
	int n[8];
	int c = nodeID1;
	int nNodesPerLayer = nnodes.x * nnodes.y;
	int elID = elementID1;
	bool stop = false;

	int maxPhi_i = completeRev ? nnodes.y : nnodes.y - 1;

	for (int iz = 0; iz < (nnodes.z - 1); iz++) {
		for (int ix = 0; ix < (nnodes.x - 1); ix++) {
			for (int iphi = 0; iphi < maxPhi_i; iphi++) {

				bool endOfCircle = (iphi == (nnodes.y - 1));

				n[0] = c + nNodesPerLayer;
				n[1] = n[0] + 1;			//
				n[2] = n[1] + nnodes.y;		//
				n[3] = n[2] - 1;
				n[4] = c;
				n[5] = n[4] + 1;			//
				n[6] = n[5] + nnodes.y;		//
				n[7] = n[6] - 1;

				if (endOfCircle && completeRev) {
					n[1] -= nnodes.y; n[2] -= nnodes.y; n[5] -= nnodes.y; n[6] -= nnodes.y;
				}

				c++;
				feaWriter->write8nodedHexa(elID++, n);

				if (false && (elID > (1 + nNodesPerLayer - nnodes.y))) {
					stop = true;
					break;
				}

			}
			if (!completeRev)
				c += 1;
			if (stop) break;
		}		
		c += (1 * nnodes.y);
		/*if (!completeRev)
			c -= 1;*/
		if (stop) break;
	}

}
int Mesh3DTubular::numberOfNodes() {
	return nnodes.x * nnodes.y * nnodes.z;
}
int Mesh3DTubular::numberOfElements() {
	if(completeRev)
		return (nnodes.x - 1) * nnodes.y * (nnodes.z - 1);
	else
		return (nnodes.x - 1) * (nnodes.y - 1) * (nnodes.z - 1);
}

std::vector<int> Mesh3DTubular::getEdgeNodeIds(edge edge_id) {
	currentEdgeIteration = 0;
	currentEdgeNodeIDs.clear();
	currentEdge = edge_id;

	int id = nodeID1;
	int nFaceNodes = nnodes.x * nnodes.y;
	switch (edge_id)
	{
	case Mesh3DTubular::edge::edge_inner_z: id += 0; break;
	case Mesh3DTubular::edge::edge_outer_z: id += (nFaceNodes - nnodes.y); break;
	default:break;
	}

	for (int i = 0; i < nnodes.z; i++) {
		currentEdgeNodeIDs.push_back(id);
		id += nFaceNodes;
	}

	maxEdgeIteration = nnodes.y;
	currentEdgeIteration = 1;

	return currentEdgeNodeIDs;
}
std::vector<int> Mesh3DTubular::getNextEdge() {

	if (currentEdgeIteration >= maxEdgeIteration)
		return std::vector<int>();

	for (int& id : currentEdgeNodeIDs)
		id += 1;

	currentEdgeIteration++;
	return currentEdgeNodeIDs;
}


int createElementsBetweenTube(
	FEAwriter* feaWriter,
	Mesh3DTubular*		tubeOuter,
	Mesh3DTubular*		tubeInner,
	int				elStartID)
{
	std::vector<int> edge1 = tubeOuter->getEdgeNodeIds(Mesh3DTubular::edge::edge_inner_z);
	std::vector<int> edge2 = tubeInner->getEdgeNodeIds(Mesh3DTubular::edge::edge_outer_z);
	std::vector<int> nextEdge1 = tubeOuter->getNextEdge();
	std::vector<int> nextEdge2 = tubeInner->getNextEdge();

	int elID = elStartID;
	while ((nextEdge1.size() > 0) && (nextEdge2.size() > 0))
	{
		elID = feaWriter->writeElementRow(edge2, edge1, nextEdge1, nextEdge2, elID);

		edge1 = nextEdge1;
		edge2 = nextEdge2;
		nextEdge1 = tubeOuter->getNextEdge();
		nextEdge2 = tubeInner->getNextEdge();
	}

	if(tubeInner->hasCompleteRevolution() && tubeOuter->hasCompleteRevolution()){
		nextEdge1 = tubeOuter->getEdgeNodeIds(Mesh3DTubular::edge::edge_inner_z);
		nextEdge2 = tubeInner->getEdgeNodeIds(Mesh3DTubular::edge::edge_outer_z);
		elID = feaWriter->writeElementRow(edge2, edge1, nextEdge1, nextEdge2, elID);
	}
	return elID;
}