#include "PrimitiveMeshGenerator.h"



PrimitiveMeshGenerator::PrimitiveMeshGenerator()
{
}

int PrimitiveMeshGenerator::processInputParameters(const std::map<std::string, std::vector<std::string>>& parameters) {

	if (parameters.find("p") != parameters.end()) {
		primitiveType = getPrimitiveMeshType(parameters.at("p")[0]);
	}

	return 0;
}

int PrimitiveMeshGenerator::generate() {

	glm::dvec3 pos(0);
	switch (primitiveType)
	{
	case primitive_mesh_type::PLATE_2D:
		break;
	case primitive_mesh_type::PLATE_2D_REF_SIDE:
		mesh = new Mesh2DPlateRefSide(pos, glm::dvec2(14.0, 19.1), 7, 1.2, 3);
		break;
	case primitive_mesh_type::TUBE_2D:
		mesh = new Mesh2DPipe(pos, 8.0, 41, glm::dvec2(1.0, 1.0));
	case primitive_mesh_type::TUBE_2D_REF_SIDE:
	case primitive_mesh_type::TUBE_3D:
		mesh = new Mesh3DPipe(pos, 10.0, 20.0, 8, glm::dvec3(2.0, 2.0, 2.0));
		break;
	case primitive_mesh_type::CUBE_3D:
		break;
	case primitive_mesh_type::CUBE_3D_REF_SIDE:
		mesh = new Mesh3DCuboidRefFace(pos, glm::dvec3(10, 30, 5), 0.1, 2.5, 3);
		break;
	case primitive_mesh_type::TUBE_REC_3D:
		mesh = new Mesh3DElipsToRec(pos, glm::dvec2(10.0, 10.0), glm::dvec2(2.5), 5.0, glm::dvec3(1.0));
		break;
		
	default:
		break;
	}
	nodeRegions.push_back(mesh);

	return 0;
}

void PrimitiveMeshGenerator::writeConnectionElements(std::ofstream& file){}