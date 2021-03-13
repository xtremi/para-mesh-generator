#include "Mesh3DCubeS.h"


Mesh3DCubeS::Mesh3DCubeS(const glm::dvec3& _pos, const glm::dvec2& _surfaceLengths, direction _extrudeDirection)
	: Mesh3DCuboid(_pos, glm::dvec3(_surfaceLengths.x, _surfaceLengths.y, 0.0))
{
	extrudeDirection = _extrudeDirection;
}

Mesh3DCubeS::Mesh3DCubeS(const glm::dvec3& _pos, const glm::dvec2& _surfaceLengths, direction _extrudeDirection, const glm::ivec2 _surfNnodes)
	: Mesh3DCubeS(_pos, _surfaceLengths, _extrudeDirection)
{
	surfNnodes = _surfNnodes;

	surfElsize = surfaceLengths / (glm::dvec2)(surfNnodes - glm::ivec2(1));
}

Mesh3DCubeS::Mesh3DCubeS(const glm::dvec3& _pos, const glm::dvec2& _surfaceLengths, direction _extrudeDirection, const glm::dvec2 _surfElsize)
	: Mesh3DCubeS(_pos, _surfaceLengths, _extrudeDirection)
{
	surfElsize = _surfElsize;

	surfNnodes = (glm::ivec2)(surfaceLengths / surfElsize) + glm::ivec2(1);
	surfElsize = surfaceLengths / (glm::dvec2)(surfNnodes - glm::ivec2(1));
}



Mesh3DCubeS::Mesh3DCubeS(const Mesh3DCubeS& rhs)
	: Mesh3DCuboid(rhs.pos, rhs.length)
{
	//to do, copy correctly
}

/*

surface
 ___ ___ ___ ___
|   |   |   |   |
|___|___|___|___|
|   |   |   |   |
|___|___|___|___|
|   |   |   |   |
|___|___|___|___|
|   |   |   |   |
|___|___|___|___|

*/
void Mesh3DCubeS::extrudeSection(double length, int nnodes)
{
	extruded_section exs(length);
	exs.nnodes = nnodes;

	double elsize = length / (double)(nnodes - 1);
	exs.elEndSize = elsize;
	exs.elStartSize = elsize;

	sections.push_back(exs);
}

void Mesh3DCubeS::extrudeSection(double length, double elsize)
{
	extruded_section exs(length);	
	exs.nnodes = (int)(length / elsize) + 1;
	elsize = length / (double)(exs.nnodes - 1);
	exs.elEndSize   = elsize;
	exs.elStartSize = elsize;

	sections.push_back(exs);
}

void Mesh3DCubeS::extrudeSectionLinearIncrease(double length, double startElSize, double endElSize) 
{
	extruded_section exs(length);
	exs.length = length;
	exs.elStartSize = startElSize;
	exs.elEndSize   = endElSize;

	sections.push_back(exs);
}

void Mesh3DCubeS::writeNodes(FEAwriter* writer)
{
	int nodeID = nodeID1;
	glm::dvec3 curPos = pos;

	for(int i = 0; i < sections.size(); i++){
		for (int j = 0; j < sections[i].nnodes; j++){

			if (extrudeDirection == direction::x) {
				writer->writeNodePlaneYZ(pos, surfElsize, surfNnodes, nodeID++);
			}
			else if (extrudeDirection == direction::y) {
				writer->writeNodePlaneXZ(pos, surfElsize, surfNnodes, nodeID++);
			}
			else if (extrudeDirection == direction::z) {
				writer->writeNodePlaneXY(pos, surfElsize, surfNnodes, nodeID++);
			}
		}
	}
}

void Mesh3DCubeS::writeElements(FEAwriter* writer) 
{
	writer->writeElementsCubeXZY(glm::ivec3(0,0,0), nodeID1, elementID1);
}


int Mesh3DCubeS::numberOfNodes() {
	return totalNodes;
}
int Mesh3DCubeS::numberOfElements() {
	return totalElements;
}