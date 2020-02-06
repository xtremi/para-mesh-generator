#include "CBeam3DMeshGenerator.h"



CBeam3DMeshGenerator::CBeam3DMeshGenerator() 
	: MeshGenerator()
{
	valid_parameters = { "h", "w_top", "w_bot", "t_top", "t_bot", "t_mid", "r", "l", "elsize" };
	param_values = { &h,  &w_top,  &w_bot,  &t_top,  &t_bot,  &t_mid,  &r,  &l,  &elsize };
}


CBeam3DMeshGenerator::~CBeam3DMeshGenerator()
{
}


int CBeam3DMeshGenerator::generate()
{
	calculateInitalVariables();
	
	glm::dvec3 web_size(t_mid, h - t_bot - t_top, l);

	glm::dvec3 flt_sizeL(t_mid,			t_top, l);
	glm::dvec3 flt_sizeR(w_top - t_mid, t_top, l);
	
	glm::dvec3 flb_sizeL(t_mid,			t_bot, l);
	glm::dvec3 flb_sizeR(w_bot - t_mid, t_bot, l);

	Mesh3DCube* web_block = new Mesh3DCube(w1, web_size, glm::dvec3(elsize));

	glm::dvec3 dy = glm::dvec3(0, web_block->elsize.y, 0);	
	Mesh3DCube* flange_top_left = new Mesh3DCube(ft1 + dy, flt_sizeL - dy, glm::dvec3(elsize));

	glm::dvec3 dx = glm::dvec3(web_block->elsize.x, 0, 0);
	Mesh3DCube* flange_top_right = new Mesh3DCube(ft2 + dx, flt_sizeR - dx, glm::dvec3(elsize));

	Mesh3DCube* flange_bot_left  = new Mesh3DCube(fb1,		flb_sizeL - dy, glm::dvec3(elsize));
	Mesh3DCube* flange_bot_right = new Mesh3DCube(fb2 + dx, flb_sizeR - dx, glm::dvec3(elsize));

	nodeRegions.push_back(web_block);
	nodeRegions.push_back(flange_top_left);
	nodeRegions.push_back(flange_top_right);
	nodeRegions.push_back(flange_bot_left);
	nodeRegions.push_back(flange_bot_right);
	return 0;
}


/*

  _______   __________
 |	 FT1 | |		  |
 |_______| |	FT2	  |
  _______  |__________|
 |       |
 |       |
 |       |
 |   W1  |
 |       |
 |       |
 |_______|  __________
  _______  |		  |
 |  FB1  | |	FB2	  |
 |_______| |__________|

*/
void CBeam3DMeshGenerator::writeConnectionElements(std::ofstream& file) 
{
	Mesh3DCube* w1  = (Mesh3DCube*)nodeRegions[0];
	Mesh3DCube* ft1 = (Mesh3DCube*)nodeRegions[1];
	Mesh3DCube* ft2 = (Mesh3DCube*)nodeRegions[2];
	Mesh3DCube* fb1 = (Mesh3DCube*)nodeRegions[3];
	Mesh3DCube* fb2 = (Mesh3DCube*)nodeRegions[4];	

	int elID = nodeRegions[4]->numberOfElements() + nodeRegions[4]->firstElementID();

	elID = createElementsBetweenCubes(file, ft2, ft1, Mesh3DCube::edge::edge67, Mesh3DCube::edge::edge58, false, false, elID, format);
	elID = createElementsBetweenCubes(file, fb2, fb1, Mesh3DCube::edge::edge23, Mesh3DCube::edge::edge14, true, true, elID, format);

	elID = createElementsBetweenCubes(file, ft1, w1, Mesh3DCube::edge::edge14, Mesh3DCube::edge::edge58, false, true, elID, format);
	elID = createElementsBetweenCubes(file, w1, fb1, Mesh3DCube::edge::edge14, Mesh3DCube::edge::edge58, false, true, elID, format);

	std::vector<int> ebl, ebr, etr, etl;
	ebl = ft2->getEdgeNodeIds(Mesh3DCube::edge::edge23);
	etl = ft2->getNextEdge();
	ebr = w1->getEdgeNodeIds(Mesh3DCube::edge::edge58);
	etr = ft1->getEdgeNodeIds(Mesh3DCube::edge::edge14);
	elID = writeElementRow(file, format, ebl, ebr, etr, etl, elID);

	etl = fb2->getEdgeNodeIds(Mesh3DCube::edge::edge67, false);
	ebl = fb2->getNextEdge();
	ebr = fb1->getEdgeNodeIds(Mesh3DCube::edge::edge58);
	etr = w1->getEdgeNodeIds(Mesh3DCube::edge::edge14);
	elID = writeElementRow(file, format, ebl, ebr, etr, etl, elID);
	
}



/*
 ____________________
|       |	         |   
|	  	|            |
|_______|____________| 
|FT1    |FT2
|       |
|       |
|       |
|0----->|
|       |
|       |
|       |
|_______|___________
|W1	    |	        |
|	    |	        |
|_______|___________|
 FB1     FB2

*/
int CBeam3DMeshGenerator::calculateInitalVariables()
{
	ft1 = glm::dvec3(0.0,   h / 2.0 - t_top, 0.0);
	ft2 = glm::dvec3(t_mid, h / 2.0 - t_top, 0.0);

	fb1 = glm::dvec3(0.0, -(h / 2.0), 0.0);
	fb2 = glm::dvec3(t_mid, -(h / 2.0), 0.0);

	w1 = glm::dvec3(0.0, -(h / 2.0 - t_bot), 0.0);

	int web_n_el_x = (int)(t_mid / elsize);
	elsize = t_mid / (double)web_n_el_x;
	return 0;
}