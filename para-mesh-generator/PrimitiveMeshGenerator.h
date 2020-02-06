#pragma once
#include "MeshGenerator.h"

#include "Mesh2DPlate.h"
#include "Mesh2DPlateRefSide.h"
#include "Mesh3DCube.h"
#include "Mesh3DCuboidRefFace.h"
#include "Mesh3DElipsToRec.h"
#include "Mesh3DPipe.h"
#include "Mesh2DPipe.h"


class PrimitiveMeshGenerator :
	public MeshGenerator
{
public:
	PrimitiveMeshGenerator();
	int processInputParameters(const std::map<std::string, std::vector<std::string>>& parameters);

	int generate();

	void writeConnectionElements(std::ofstream& file);

private:
	primitive_mesh_type primitiveType = primitive_mesh_type::CUBE_3D;
	MeshPrimitive* mesh = NULL;


};

