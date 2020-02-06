#pragma once
#include "mesh_types.h"

const int NUMBER_OF_FORMAT_TYPE = 3;
const int NUMBER_OF_MESH_TYPES = 9;
const int NUMBER_MESH_PRIMITIVE_TYPES = 9;

const std::string primitive_mesh_type_names[] =
{   
	"PLATE_2D,",
	"PLATE_2D_REF_SIDE",
	"CUBE_3D",
	"CUBE_3D_REF_SIDE",
	"TUBE_2D",
	"TUBE_2D_REF_SIDE",
	"TUBE_3D",
	"TUBE_3D_REF_SIDE",
	"TUBE_REC_3D"
};

const std::string format_type_names[NUMBER_OF_FORMAT_TYPE] =
{	"ANSYS",
	"NASTRAN",
	"ABAQUS"
};

const std::string mesh_type_names[NUMBER_OF_MESH_TYPES] = 
	{	
		"I_BEAM_3D", 
		"C_BEAM_3D", 
		"PIPE_BEAM_3D",
		"CYLINDER_BEAM_3D",
		"HOLED_PLATE_3D",
		"BOX_3D", 
		"PLATE_2D", 
		"CIRCLE_2D",
		"PRIMITIVE"
	};

const std::map<std::string, primitive_mesh_type> primitive_mesh_type_map = {
	{"PLATE_2D",			primitive_mesh_type::PLATE_2D},
	{"PLATE_2D_REF_SIDE",	primitive_mesh_type::PLATE_2D_REF_SIDE},
	{"TUBE_3D",				primitive_mesh_type::TUBE_3D},
	{"TUBE_3D_REF_SIDE",	primitive_mesh_type::TUBE_3D_REF_SIDE},
	{"TUBE_2D",				primitive_mesh_type::TUBE_2D},
	{"TUBE_2D_REF_SIDE",	primitive_mesh_type::TUBE_2D_REF_SIDE},
	{"CUBE_3D",				primitive_mesh_type::CUBE_3D},
	{"CUBE_3D_REF_SIDE",	primitive_mesh_type::CUBE_3D_REF_SIDE},
	{"TUBE_REC_3D",			primitive_mesh_type::TUBE_REC_3D}
};

const std::map<std::string, format_type> format_type_map = {
	{"ANSYS",	format_type::ANSYS},
	{"NASTRAN",	format_type::NASTRAN},
	{"ABAQUS",	format_type::ABAQUS}
};

const std::map<std::string, mesh_type> mesh_type_map = {
	{"I_BEAM_3D",	mesh_type::I_BEAM_3D},
	{"C_BEAM_3D",	mesh_type::C_BEAM_3D},
	{"PIPE_BEAM_3D",	mesh_type::PIPE_BEAM_3D},
	{"CYLINDER_BEAM_3D",	mesh_type::CYLINDER_BEAM_3D},
	{"HOLED_PLATE_3D",	mesh_type::HOLED_PLATE_3D},
	{"BOX_3D",		mesh_type::BOX_3D},
	{"PLATE_2D",	mesh_type::PLATE_2D},
	{"CIRCLE_2D",	mesh_type::CIRCLE_2D},
	{"PRIMITIVE",	mesh_type::PRIMITIVE}
};


std::string getPrimitiveMeshTypeName(primitive_mesh_type meshType) {
	return primitive_mesh_type_names[(int)meshType];
}
primitive_mesh_type getPrimitiveMeshType(const std::string& str) {
	if (primitive_mesh_type_map.find(str) != primitive_mesh_type_map.end())
		return primitive_mesh_type_map.at(str);
	return primitive_mesh_type::CUBE_3D;
}

std::string getFormatTypeName(format_type format) {
	return format_type_names[(int)format];
}
format_type getFormatType(const std::string& str) {
	if (format_type_map.find(str) != format_type_map.end())
		return format_type_map.at(str);
	return format_type::NASTRAN;
}

std::string getMeshTypeName(mesh_type meshType) {
	return mesh_type_names[(int)meshType];
}

mesh_type getMeshType(const std::string& str) {
	if(mesh_type_map.find(str) != mesh_type_map.end())
		return mesh_type_map.at(str);
	return mesh_type::BOX_3D;
}