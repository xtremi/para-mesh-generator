#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "string_utilities.h"
#include "mesh_types.h"
#include "glm/glm.hpp"


class FEAwriter {
public:
	FEAwriter(std::ofstream* _file) { file = _file; }
	virtual void writeNode(int nodeID, const glm::dvec3& c) = 0;
	virtual void write4nodedShell(int elID, int n[4]) = 0;
	virtual void write8nodedHexa(int elID, int n[8]) = 0;
	void writePreNodes(int numberOfNodes = -1){}
	void writePostNodes(){}
	void writePreElements(int numberOfElements = -1){}
	void writePostElements(){}
	void setElementDim(element_dim_type _eldim) { eldim = _eldim; }

	int writeNodeRowX(
		const glm::dvec3&	spos,
		double dx, int nrows, int nodeIDstart);

	int writeNodeRowY(
		const glm::dvec3&	spos,
		double dy, int nrows, int nodeIDstart);

	int writeNodeRowZ(
		const glm::dvec3&	spos,
		double dz, int nrows, int nodeIDstart);

	int writeNodeRow(
		const glm::dvec3&	spos,
		const glm::dvec3& d, int nrows, int nodeIDstart);

	int writeNodePlaneXY(
		const glm::dvec3&	spos,
		const glm::dvec2&	dxy,
		const glm::ivec2&	nnodes,
		int nodeIDstart);

	int writeNodePlaneXZ(
		const glm::dvec3&	spos,
		const glm::dvec2&	dxz,
		const glm::ivec2&	nnodes,
		int nodeIDstart);

	int writeNodeCuboidXZY(
		const glm::dvec3&	spos,
		const glm::dvec3&	dxy,
		const glm::ivec3&	nnodes,
		int nodeIDstart);

	int writeElementsPlaneXY(
		glm::ivec2			nnodes,
		int					nodeID1,
		int					elementID1
	);

	int writeElementsCubeXZY(
		glm::ivec3			nnodes,
		int					nodeID1,
		int					elementID1
	);

	int writeElementRow(
		const std::vector<int>& bl,
		const std::vector<int>& br,
		const std::vector<int>& tr,
		const std::vector<int>& tl,
		int elStartID);



protected:
	std::ofstream* file = NULL;

	element_dim_type eldim;
};


class NastranFEAwriter : public FEAwriter {
public:
	NastranFEAwriter(std::ofstream* _file) : FEAwriter(_file) {};
	void writeNode(int nodeID, const glm::dvec3& c);
	void write4nodedShell(int elID, int n[4]);
	void write8nodedHexa(int elID, int n[8]);
};

class AbaqusFEAwriter : public FEAwriter {
public:
	AbaqusFEAwriter(std::ofstream* _file) : FEAwriter(_file) {}
	void writeNode(int nodeID, const glm::dvec3& c);
	void write4nodedShell(int elID, int n[4]);
	void write8nodedHexa(int elID, int n[8]);

	void writePreNodes(int numberOfNodes = -1);
	void writePreElements(int numberOfNodes = -1);
};

class AnsysFEAwriter : public FEAwriter {
public:
	AnsysFEAwriter(std::ofstream* _file) : FEAwriter(_file) {};
	void writeNode(int nodeID, const glm::dvec3& c);
	void write4nodedShell(int elID, int n[4]);
	void write8nodedHexa(int elID, int n[8]);

	void writePreNodes(int numberOfNodes = -1);
	void writePreElements(int numberOfNodes = -1);	
};

class VTKFEAwriter : public FEAwriter {
public:
	VTKFEAwriter(std::ofstream* _file) : FEAwriter(_file) {};
	void writeNode(int nodeID, const glm::dvec3& c);
	void write4nodedShell(int elID, int n[4]);
	void write8nodedHexa(int elID, int n[8]);

	void writePreNodes(int numberOfNodes = -1);
	void writePreElements(int numberOfNodes = -1);
};


void writeVectorCommaDelimeted(std::ofstream& file, int* vec, int size);
void writeVectorSpaceDelimeted(std::ofstream& file, int* vec, int size);

/*void writeNode(std::ofstream& file, int nodeID, const glm::dvec3& c, format_type format);
void write4nodedShell(std::ofstream& file, int elID, int n[4], format_type format);
void write8nodedHexa(std::ofstream& file, int elID, int n[8], format_type format);


void writeNastranNode(std::ofstream& file, int nodeID, const glm::dvec3& c);
void writeAbaqusNode(std::ofstream& file, int nodeID, const glm::dvec3& c);
void writeAnsysNode(std::ofstream& file, int nodeID, const glm::dvec3& c);
void writeVTKNode(std::ofstream& file, int nodeID, const glm::dvec3& c);

void writeAbaqusS4R(std::ofstream& file, int elID, int n[4]);
void writeAbaqusC3D8R(std::ofstream& file, int elID, int n[8]);

void writeNastranCquad4(std::ofstream& file, int elID, int n[4]);
void writeNastranChexa8(std::ofstream& file, int elID, int n[8]);

void writeAnsysShell181(std::ofstream& file, int elID, int n[4]);
void writeAnsysSolid185(std::ofstream& file, int elID, int n[8]);

void writeVTKQuad9(std::ofstream& file, int elID, int n[4]);
void writeVTKHexahedron12(std::ofstream& file, int elID, int n[8]);*/
