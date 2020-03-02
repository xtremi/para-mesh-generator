#pragma once
#include <map>
#include <string>

enum class element_dim_type {
	e2D,
	e3D
};

enum class format_type {
	ANSYS,
	NASTRAN,
	ABAQUS,
	VTK
};

enum class mesh_type { 
	I_BEAM_3D,
	C_BEAM_3D,
	PIPE_BEAM_3D,
	CYLINDER_BEAM_3D,
	HOLED_PLATE_3D,
	BOX_3D,
	PLATE_2D,
	CIRCLE_2D,
	PRIMITIVE
};

enum class primitive_mesh_type {
	PLATE_2D,
	PLATE_2D_REF_SIDE,
	CUBE_3D,
	CUBE_3D_REF_SIDE,
	TUBE_2D,
	TUBE_2D_REF_SIDE,
	TUBE_3D,
	TUBE_3D_REF_SIDE,
	TUBE_REC_3D,
};

extern const int NUMBER_MESH_PRIMITIVE_TYPES;
extern const int NUMBER_OF_FORMAT_TYPE;
extern const int NUMBER_OF_MESH_TYPES;

extern const std::string primitive_mesh_type_names[];
extern const std::string format_type_names[];
extern const std::string mesh_type_names[];

extern const std::map<std::string, primitive_mesh_type> primitive_mesh_type_map;
extern const std::map<std::string, format_type> format_type_map;
extern const std::map<std::string, mesh_type> mesh_type_map;

std::string getPrimitiveMeshTypeName(primitive_mesh_type meshType);
primitive_mesh_type getPrimitiveMeshType(const std::string& str);

std::string getFormatTypeName(format_type format);
format_type getFormatType(const std::string& str);

std::string getMeshTypeName(mesh_type meshType);
mesh_type getMeshType(const std::string& str);