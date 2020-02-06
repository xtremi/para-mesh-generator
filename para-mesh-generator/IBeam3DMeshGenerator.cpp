#pragma once
#include "IBeam3DMeshGenerator.h"
#include "Mesh3DCube.h"

IBeam3DMeshGenerator::IBeam3DMeshGenerator() 
	: MeshGenerator()
{
	valid_parameters	= { "h", "w_top", "w_bot", "t_top", "t_bot", "t_mid", "r", "l", "elsize" };
	param_values		= { &h,  &w_top,  &w_bot,  &t_top,  &t_bot,  &t_mid,  &r,  &l,  &elsize };
}
IBeam3DMeshGenerator::~IBeam3DMeshGenerator(){}



int IBeam3DMeshGenerator::generate()
{	
	calculateInitalVariables();

	glm::dvec3 web_size(t_mid, h - t_bot - t_top, l);

	glm::dvec3 flt_sizeL(0.5*(w_top - t_mid), t_top, l);
	glm::dvec3 flt_sizeC(t_mid, t_top, l);
	glm::dvec3 flt_sizeR = flt_sizeL;

	glm::dvec3 flb_sizeL(0.5*(w_bot - t_mid), t_bot, l);
	glm::dvec3 flb_sizeC(t_mid, t_bot, l);
	glm::dvec3 flb_sizeR = flb_sizeL;

	Mesh3DCube* web_block1		= new Mesh3DCube(w1, web_size, glm::dvec3(elsize));

	glm::dvec3 dx = glm::dvec3(web_block1->elsize.x, 0, 0);		
	Mesh3DCube* flange_top_left	= new Mesh3DCube(ft1 , flt_sizeL - dx, glm::dvec3(elsize));
	
	glm::dvec3 dy = glm::dvec3(0, flange_top_left->elsize.y, 0);
	Mesh3DCube* flange_top_center = new Mesh3DCube(ft2 + dy, flt_sizeC - dy, glm::dvec3(elsize));

	Mesh3DCube* flange_top_right = new Mesh3DCube(ft3 + dx, flt_sizeR - dx, glm::dvec3(elsize));


	Mesh3DCube* flange_bot_left = new Mesh3DCube(fb1, flb_sizeL - dx, glm::dvec3(elsize));
	Mesh3DCube* flange_bot_center = new Mesh3DCube(fb2, flb_sizeC - dy, glm::dvec3(elsize));
	Mesh3DCube* flange_bot_right = new Mesh3DCube(fb3 + dx, flb_sizeR - dx, glm::dvec3(elsize));

	nodeRegions.push_back(web_block1);
	nodeRegions.push_back(flange_top_left);
	nodeRegions.push_back(flange_top_center);
	nodeRegions.push_back(flange_top_right);
	nodeRegions.push_back(flange_bot_left);
	nodeRegions.push_back(flange_bot_center);
	nodeRegions.push_back(flange_bot_right);
	return 0;
}


/*

 ___________   _______   __________
|  			| |	 FT2  |	|		   |   
|	FT1		| |_______|	|	FT3	   |
|___________|  _______  |__________|    
	 		  |       |
	 		  |       |
	 		  |       |
	 		  |   W1  |
	 		  |       |
	 		  |       |
 ___________  |_______|  __________
|  			|  _______	|		   |
|	FB1		| |  FB2  |	|	FB3	   |
|___________| |_______| |__________|

8
@ + + + + + + + + + + + @ 7
+\                      +\
+ \                     + \
+  \                    +  \
+   \ 5                 +   \ 6
+    @ + + + + + + + + +++ + @
+    +                  +    +
+    +                  +    +
+    +                  +    +
+    +                  +    +
+    +                  +    +
+ 4  +                  +    +
@ + +++ + + + + + + + + @ 3  +
 \   +                   \   +
  \  +                    \  +
   \ +                     \ +
	\+                      \+
	 @ + + + + + + + + + + + @
     1                       2

*/
void IBeam3DMeshGenerator::writeConnectionElements(std::ofstream& file)
{
	Mesh3DCube* w1 = (Mesh3DCube*)nodeRegions[0];
	Mesh3DCube* fb1 = (Mesh3DCube*)nodeRegions[4];
	Mesh3DCube* fb2 = (Mesh3DCube*)nodeRegions[5];
	Mesh3DCube* fb3 = (Mesh3DCube*)nodeRegions[6];

	Mesh3DCube* ft1 = (Mesh3DCube*)nodeRegions[1];
	Mesh3DCube* ft2 = (Mesh3DCube*)nodeRegions[2];
	Mesh3DCube* ft3 = (Mesh3DCube*)nodeRegions[3];

	int elID = nodeRegions[6]->numberOfElements() + nodeRegions[6]->firstElementID();
	elID = createElementsBetweenCubes(file, fb1, fb2, Mesh3DCube::edge::edge14, Mesh3DCube::edge::edge23, true, true, elID, format);
	elID = createElementsBetweenCubes(file, fb3, fb2, Mesh3DCube::edge::edge23, Mesh3DCube::edge::edge14, true, true, elID, format);
	elID = createElementsBetweenCubes(file, ft1, ft2, Mesh3DCube::edge::edge58, Mesh3DCube::edge::edge67, false, false, elID, format);
	elID = createElementsBetweenCubes(file, ft3, ft2, Mesh3DCube::edge::edge67, Mesh3DCube::edge::edge58, false, false, elID, format);

	elID = createElementsBetweenCubes(file, fb2, w1, Mesh3DCube::edge::edge56, Mesh3DCube::edge::edge12, true, false, elID, format);
	elID = createElementsBetweenCubes(file, ft2, w1, Mesh3DCube::edge::edge12, Mesh3DCube::edge::edge56, false, true, elID, format);

	std::vector<int> ebl, ebr, etr, etl;
	ebl = fb2->getEdgeNodeIds(Mesh3DCube::edge::edge67);
	etr = fb1->getEdgeNodeIds(Mesh3DCube::edge::edge58, false);
	ebr = fb1->getNextEdge();
	etl = w1->getEdgeNodeIds(Mesh3DCube::edge::edge23);	
	elID = writeElementRow(file, format, ebl, ebr, etr, etl, elID);

	etl = fb3->getEdgeNodeIds(Mesh3DCube::edge::edge67, false);
	ebl = fb3->getNextEdge();
	ebr = fb2->getEdgeNodeIds(Mesh3DCube::edge::edge58);
	etr = w1->getEdgeNodeIds(Mesh3DCube::edge::edge14);
	elID = writeElementRow(file, format, ebl, ebr, etr, etl, elID);

	ebl = ft3->getEdgeNodeIds(Mesh3DCube::edge::edge23);
	etl = ft3->getNextEdge();
	ebr = w1->getEdgeNodeIds(Mesh3DCube::edge::edge58);
	etr = ft2->getEdgeNodeIds(Mesh3DCube::edge::edge14);
	elID = writeElementRow(file, format, ebl, ebr, etr, etl, elID);

	ebl = w1->getEdgeNodeIds(Mesh3DCube::edge::edge67);
	ebr = ft1->getEdgeNodeIds(Mesh3DCube::edge::edge14);
	etr = ft1->getNextEdge();
	etl = ft2->getEdgeNodeIds(Mesh3DCube::edge::edge23);
	elID = writeElementRow(file, format, ebl, ebr, etr, etl, elID);

}

/*

 __________________________________   
|  			  |	  |	  |			   |
|			  |	  |	  |			   |
|_____________|___|___|____________|
 FT1 ^        |FT2    |FT3 
	 |		  |       |
	 |		  |       |
	 |		  |       |
	 |		  |       |
	 |        |<--0-->| web_n_el_x  
	 |        |       |
	 |		  |       |
	 |		  |       |
	 |		  |       |
 ____v________|_______|____________
|			W1|	  |	  |			   |
|			  |	  |	  |			   |
|_____________|___|___|____________|
FB1			   FB2	   FB3

*/
int IBeam3DMeshGenerator::calculateInitalVariables()
{
	ft1 = glm::dvec3(-w_top / 2.0, h / 2.0 - t_top, 0.0);
	ft2 = glm::dvec3(-t_mid / 2.0, h / 2.0 - t_top, 0.0);
	ft3 = glm::dvec3(t_mid / 2.0, h / 2.0 - t_top, 0.0);

	fb1 = glm::dvec3(-w_bot / 2.0, -(h / 2.0), 0.0);
	fb2 = glm::dvec3(-t_mid / 2.0, -(h / 2.0), 0.0);
	fb3 = glm::dvec3(t_mid / 2.0, -(h / 2.0), 0.0);

	w1 = glm::dvec3(-t_mid / 2.0, -(h/2.0 - t_bot), 0.0);

	int web_n_el_x = (int)(t_mid / elsize);	
	elsize = t_mid / (double)web_n_el_x;
	return 0;
}