#include "MeshGenerator.h"
MeshGenerator::MeshGenerator(const std::string& _filepath, format_type _format){	
	outpath = _filepath;
	format = _format;
}
MeshGenerator::~MeshGenerator(){}


int MeshGenerator::writeToFile() {

	std::ofstream file;
	file.open(outpath);
	if (!file.is_open())
		return ERR_CODE_UNABLE_TO_OPEN_FILE;
		
	switch (format)
	{
	case format_type::ANSYS:
		feaWriter = new AnsysFEAwriter(&file);
		break;
	case format_type::NASTRAN:
		feaWriter = new NastranFEAwriter(&file);
		break;
	case format_type::ABAQUS:
		feaWriter = new AbaqusFEAwriter(&file);
		break;
	case format_type::VTK:
		feaWriter = new VTKFEAwriter(&file);
		break;
	default:
		break;
	}

	writeNodes();
	writeElements();	

	file.close();
	return 0;
}

void MeshGenerator::writeNodes() {
	int idstart = 1;
	
	feaWriter->writePreNodes();

	std::cout << "Writing nodes..." << std::endl;
	for (int i = 0; i < nodeRegions.size(); i++) {
		nodeRegions[i]->setFirstNodeID(idstart);
		nodeRegions[i]->writeNodes(feaWriter);
		std::cout << "\tNODE REGION " << i + 1 << ": node " << idstart;
		idstart += nodeRegions[i]->numberOfNodes();
		std::cout << " - " << idstart << std::endl;
	}
}
void MeshGenerator::writeElements() {
	int idstart = 1;
	std::cout << "Writing elements..." << std::endl;
	if (nodeRegions.size() == 0) return;

	feaWriter->writePreElements();

	for (int i = 0; i < nodeRegions.size(); i++) {
		nodeRegions[i]->setFirstElementID(idstart);
		
		nodeRegions[i]->writeElements(feaWriter);
		std::cout << "\tELEMENT REGION " << i + 1 << ": element " << idstart;
		idstart += nodeRegions[i]->numberOfElements();
		std::cout << " - " << idstart << std::endl;
	}
	writeConnectionElements();
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




