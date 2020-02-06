#include "Mesh2DTubular.h"

Mesh2DTubular::Mesh2DTubular(const glm::dvec3& _pos, bool _completeRev)
	: Mesh2D(_pos)
{
	completeRev = _completeRev;
}

void Mesh2DTubular::writeNodes(std::ofstream& file, format_type format)
{
	int nodeID = nodeID1;
	for (int ix = 0; ix < nnodes.x; ix++) {
		for (int iphi = 0; iphi < nnodes.y; iphi++) {
			glm::dvec3 c = getCoords(ix, iphi);
			writeNode(file, nodeID++, c, format);
		}
	}	
}

void Mesh2DTubular::writeElements(std::ofstream& file, format_type format)
{
	int n[4];
	int c = nodeID1;
	int elID = elementID1;

	int maxPhi_i = completeRev ? nnodes.y : nnodes.y - 1;

	for (int ix = 0; ix < (nnodes.x - 1); ix++) {
		for (int iphi = 0; iphi < maxPhi_i; iphi++) {

			bool endOfCircle = (iphi == (nnodes.y - 1));

			n[0] = c;
			n[1] = n[0] + 1;
			n[2] = n[1] + nnodes.y;
			n[3] = n[2] - 1;

			if (endOfCircle && completeRev) {
				n[1] -= nnodes.y; n[2] -= nnodes.y;
			}

			c++;
			write4nodedShell(file, elID++, n, format);
		}
		if (!completeRev)
			c += 1;
	}

}

int Mesh2DTubular::numberOfNodes()
{
	return 0;
}

int Mesh2DTubular::numberOfElements()
{
	return 0;
}