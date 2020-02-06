#include "MeshGenerator.h"
MeshGenerator::MeshGenerator(){}
MeshGenerator::~MeshGenerator(){}


int MeshGenerator::writeToFile(const std::string& filepath, format_type _format, const std::string& _stlpath) {

	std::ofstream file;
	outpath = filepath;
	format = _format;
	stlpath = _stlpath;

	file.open(outpath);
	if (!file.is_open())
		return ERR_CODE_UNABLE_TO_OPEN_FILE;
	
	
	writeNodes(file);
	writeElements(file);
	
	file.close();

	return 0;
}

void MeshGenerator::writeNodes(std::ofstream& file) {
	int idstart = 1;
	
	if (format == format_type::ANSYS) {
		file << "/prep7\n";
	}

	if (format == format_type::ABAQUS) {
		file << "*Node\n";
	}

	std::cout << "Writing nodes..." << std::endl;
	for (int i = 0; i < nodeRegions.size(); i++) {
		nodeRegions[i]->setFirstNodeID(idstart);
		nodeRegions[i]->writeNodes(file, format);
		std::cout << "\tNODE REGION " << i + 1 << ": node " << idstart;
		idstart += nodeRegions[i]->numberOfNodes();
		std::cout << " - " << idstart << std::endl;
	}
}
void MeshGenerator::writeElements(std::ofstream& file) {
	int idstart = 1;
	std::cout << "Writing elements..." << std::endl;
	if (nodeRegions.size() == 0) return;

	//Assume all noderegions are the same type of elements:
	if (format == format_type::ABAQUS) {
		if (nodeRegions[0]->el_dim() == element_dim_type::e2D)
			file << "*Element, type=S4R\n";
		else
			file << "*Element, type=C3D8R\n";
	}
	else if (format == format_type::ANSYS) {
		if (nodeRegions[0]->el_dim() == element_dim_type::e2D)
			file << "et, 1, SHELL181\nsectype, 1, SHELL,, S3D\nsecnum, 1\ntype, 1\n";
		else
			file << "et, 1, SOLID185\ntype, 1\n";
	}


	for (int i = 0; i < nodeRegions.size(); i++) {
		nodeRegions[i]->setFirstElementID(idstart);
		
		nodeRegions[i]->writeElements(file, format);
		std::cout << "\tELEMENT REGION " << i + 1 << ": element " << idstart;
		idstart += nodeRegions[i]->numberOfElements();
		std::cout << " - " << idstart << std::endl;
	}
	writeConnectionElements(file);
}


int MeshGenerator::processInputParameters(const std::map<std::string, std::vector<std::string>>& parameters) 
{
	for (int i = 0; i < valid_parameters.size(); i++) {

		std::string param = valid_parameters[i];
		
		if (parameters.find(param) != parameters.end()) {

			std::string value = parameters.at(param)[0];

			if(isReal(value)){
				(*param_values[i]) = toReal(value);
			}
		}

	}

	return 0;
}




