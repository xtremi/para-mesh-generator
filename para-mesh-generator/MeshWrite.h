#pragma once
#include "FeaWrite.h"
#include <vector>

int writeNodeRowX(
	std::ofstream&		file,	format_type			format,
	const glm::dvec3&	spos,
	double dx, int nrows, int nodeIDstart);

int writeNodeRowY(
	std::ofstream&		file,	format_type			format,
	const glm::dvec3&	spos,
	double dy, int nrows, int nodeIDstart);

int writeNodeRowZ(
	std::ofstream&		file,	format_type			format,
	const glm::dvec3&	spos,
	double dz, int nrows, int nodeIDstart);

int writeNodeRow(
	std::ofstream&		file,	format_type			format,
	const glm::dvec3&	spos,
	const glm::dvec3& d, int nrows, int nodeIDstart);

int writeNodePlaneXY(
	std::ofstream&		file,	format_type			format,
	const glm::dvec3&	spos,
	const glm::dvec2&	dxy,
	const glm::ivec2&	nnodes,
	int nodeIDstart);

int writeNodePlaneXZ(
	std::ofstream&		file,	format_type			format,
	const glm::dvec3&	spos,
	const glm::dvec2&	dxz,
	const glm::ivec2&	nnodes,
	int nodeIDstart);

int writeNodeCuboidXZY(
	std::ofstream&		file,	format_type			format,
	const glm::dvec3&	spos,
	const glm::dvec3&	dxy,
	const glm::ivec3&	nnodes,
	int nodeIDstart);

int writeElementsPlaneXY(
	std::ofstream&		file, format_type			format,
	glm::ivec2			nnodes,
	int					nodeID1,
	int					elementID1
);

int writeElementsCubeXZY(
	std::ofstream&		file,	format_type			format,
	glm::ivec3			nnodes,
	int					nodeID1,
	int					elementID1
);

int writeElementRow(
	std::ofstream& file, format_type format,
	const std::vector<int>& bl,
	const std::vector<int>& br,
	const std::vector<int>& tr,
	const std::vector<int>& tl,
	int elStartID);
