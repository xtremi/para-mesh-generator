#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include "MeshWrite.h"
#include "string_utilities.h"
#include "math_utilities.h"
#include "glm/glm.hpp"


class MeshPrimitive {
public:
	MeshPrimitive(const glm::dvec3& _pos) { pos = _pos; }

	virtual void writeNodes(std::ofstream& file, format_type format) = 0;
	virtual void writeElements(std::ofstream& file, format_type format) = 0;
	virtual int numberOfNodes() = 0;
	virtual int numberOfElements() = 0;

	void setFirstNodeID(int id);
	int firstNodeID() { return nodeID1; };
	void setFirstElementID(int id);
	int firstElementID() { return elementID1; };

	void moveX(double x);
	void moveY(double y);
	void moveZ(double z);
	void move(const glm::vec3& v);

	element_dim_type el_dim() { return _el_dim; }

protected:
	glm::dvec3 pos;
	int nodeID1 = 1;
	int elementID1 = 1;

	element_dim_type _el_dim;
};


/*

MeshPrimitive
   |
   |---Mesh2D
   |    |                        
   |    |---Mesh2DRectangle
   |    |    |                         |-- MeshSideRefinement2D
   |    |    |---Mesh2DPlate           |
   |    |    |---Mesh2DPlateRefSide----|
   |    | 
   |    |---Mesh2DTubular
   |         |                         |-- MeshCircularRefinement2D
   |         |---Mesh2DPipe            |
   |         |---#Mesh2DPipeRefFace----|
   |         |---#Mesh2DElipsToRec
   |
   |---Mesh3D
        |
        |---Mesh3DCuboid               
        |    |                         |-- MeshSideRefinement3D
		|    |---Mesh3DCube            |
        |    |---Mesh3DCuboidRefFace --|
        |
        |---Mesh3DTubular
             |                         |-- MeshCircularRefinement3D
             |---Mesh3DPipe            |
			 |---Mesh3DPipeRefFace-----|
             |---Mesh3DElipsToRec


MeshRefinement
   |
   |---MeshSideRifenement
        |
        |---MeshSideRefinement2D
        |---MeshSideRefinement3D
		|
		|---MeshCircularRefinement
		     |
			 |---MeshCircularRefinement2D
			 |---MeshCircularRefinement3D
*/