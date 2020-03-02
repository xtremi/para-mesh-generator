#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "mesh_types.h"
#include "error_codes.h"

#include "IBeam3DMeshGenerator.h"
#include "CBeam3DMeshGenerator.h"
#include "PipeBeam3DMeshGenerator.h"
#include "CylinderBeam3DMeshGenerator.h"
#include "HoledPlate3DMeshGenerator.h"
#include "Plate2DMeshGenerator.h"
#include "PrimitiveMeshGenerator.h"

/*
Inputs:
C_BEAM_3D -h 23.21 -w_top 22.14 -w_bot 12.14 -t_top 3.33 -t_mid 2.67 -t_bot 4.33 -elsize 0.88 -l 5.0
PIPE_BEAM_3D -h 20.0 -ri 6.4 -ro 9.25 -elsize 0.75
*/

struct input_parameters {
	mesh_type	meshType;
	format_type format;
	std::string outputPath;
	std::string stlfilePath;
	std::map<std::string, std::vector<std::string>> parameters;
};

int processInput(int argc, char* argv[], input_parameters* input);


int main(int argc, char* argv[])
{
	std::cout << "Para-mesh-generator" << std::endl;

	input_parameters input;
	int err = processInput(argc, argv, &input);
	if (err) return err;

	std::cout << "mesh type: " << getMeshTypeName(input.meshType) << std::endl;

	MeshGenerator* mg = nullptr;

	switch (input.meshType)
	{
	case mesh_type::BOX_3D: break;
	case mesh_type::CIRCLE_2D: break;
	case mesh_type::C_BEAM_3D: 
		mg = new CBeam3DMeshGenerator(input.outputPath, input.format);
		break;	
	case mesh_type::PLATE_2D: 
		mg = new Plate2DMeshGenerator(input.outputPath, input.format);
		break;
	case mesh_type::I_BEAM_3D: 
		mg = new IBeam3DMeshGenerator(input.outputPath, input.format);
		break;
	case mesh_type::PIPE_BEAM_3D:
		mg = new PipeBeam3DMeshGenerator(input.outputPath, input.format);
		break;
	case mesh_type::CYLINDER_BEAM_3D:
		mg = new CylinderBeam3DMeshGenerator(input.outputPath, input.format);
		break;
	case mesh_type::HOLED_PLATE_3D:
		mg = new HoledPlate3DMeshGenerator(input.outputPath, input.format);
		break;
	case mesh_type::PRIMITIVE:
		mg = new PrimitiveMeshGenerator(input.outputPath, input.format);
	default:	
		break;
	}

	if (!mg) return ERR_CODE_MESH_GENERATOR_NOT_INITIALIZED;

	if (err = mg->processInputParameters(input.parameters))
		return err;
	if (err = mg->generate())
		return err;
	if (err = mg->writeToFile())
		return err;


	return 0;
}

int processInput(int argc, char* argv[], input_parameters* input)
{
	if (argc < 2)
		return ERR_CODE_NO_INPUT_PARAMETERS;

	input->format	= format_type::NASTRAN;
	input->meshType = mesh_type::BOX_3D;
	input->stlfilePath = "";
	input->outputPath = "default_out_path.txt";

	std::string current_arg = "";
	for (int i = 1; i < argc; i++) {
		std::string val = argv[i];
		
		if (val.size() > 2 && (val[0] == '-' && val[1] == '-')) {

			current_arg = val.erase(0, 2);
			if (current_arg == "format" && (i + 1) < argc)
				input->format = getFormatType(argv[++i]);
			else if (current_arg == "mesh" && (i + 1) < argc)
				input->meshType = getMeshType(argv[++i]);
			else if (current_arg == "out" && (i + 1) < argc)
				input->outputPath = argv[++i];
			else if (current_arg == "stl" && (i + 1) < argc)
				input->stlfilePath = argv[++i];

		}
		else if (val.size() > 1 && (val[0] == '-')){
			current_arg = val.erase(0, 1);
			input->parameters[current_arg] = std::vector<std::string>();
		}
		else
			(input->parameters[current_arg]).push_back(val);
	}
	return SUCCESS_NO_ERROR;
}