#pragma once
#include "Mesh3DCuboid.h"

class Mesh3DCubeS :
	public Mesh3DCuboid
{

private:
	Mesh3DCubeS(const glm::dvec3& _pos, const glm::dvec2& _surfaceLengths, direction _extrudeDirection);
public:	
	Mesh3DCubeS(const glm::dvec3& _pos, const glm::dvec2& _surfaceLengths, direction _extrudeDirection, const glm::dvec2 _surfElsize);
	Mesh3DCubeS(const glm::dvec3& _pos, const glm::dvec2& _surfaceLengths, direction _extrudeDirection, const glm::ivec2 _surfNnodes);
	Mesh3DCubeS(const Mesh3DCubeS& rhs);

	void writeNodes(FEAwriter* writer);
	void writeElements(FEAwriter* writer);
	int numberOfNodes();
	int numberOfElements();

	void extrudeSection(double length, int nnodes);
	void extrudeSection(double length, double elsize);
	void extrudeSectionLinearIncrease(double length, double startElSize, double endElSize);

private:
	direction extrudeDirection = direction::x;
	glm::dvec2 surfaceLength;

	glm::dvec2 surfElsize;
	glm::ivec2 surfNnodes;

	glm::dvec2 surfaceLengths;	

	int totalNodes	  = 0;
	int totalElements = 0;

	struct extruded_section {
		extruded_section(double _length) { length = _length; }
		int		nnodes;
		double	length;
		double  elStartSize;
		double  elEndSize;
	};

	std::vector<extruded_section> sections;
};

