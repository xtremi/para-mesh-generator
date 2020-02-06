#pragma once
#include "MeshSideRefinement.h"


MeshSideRefinement::MeshSideRefinement(const glm::dvec2& size, int _refRows, double _elSizeNorm, double _elSizeRef)
{
	refRows    = _refRows;
	elsizeNorm = _elSizeNorm;
	elsizeRef  = _elSizeRef;

	correctRefElementSizeAndNumbers(size.x);
	refFactor = (int)glm::round(elsizeNorm / elsizeRef);
	correctRefFactor();
	normElementSizeAndNumbersFromRefFactor(size.x);

	calculateMeshSectionLengths(size.y);
}

MeshSideRefinement::MeshSideRefinement(const glm::dvec2& size, int _refRows, double _elSizeNorm, int _refFactor)
{
	refRows = _refRows;
	elsizeNorm = _elSizeNorm;

	refFactor = power_ceil(_refFactor);
	correctNormElementSizeAndNumbers(size.x);
	elsizeRef = elsizeNorm / (double)(refFactor);
	nnodesRef = (int)(size.x / elsizeRef) + 1;

	calculateMeshSectionLengths(size.y);
}

void MeshSideRefinement::correctNormElementSizeAndNumbers(double lengthx)
{
	nnodesNorm = (int)(lengthx / elsizeNorm) + 1;
	nnodesNorm = power_ceil(nnodesNorm - 1) + 1;
	elsizeNorm = lengthx / (double)(nnodesNorm - 1);
}
void MeshSideRefinement::correctRefElementSizeAndNumbers(double lengthx)
{
	nnodesRef = (int)(lengthx / elsizeRef) + 1;
	nnodesRef = power_ceil(nnodesRef - 1) + 1;
	elsizeRef = lengthx / (double)(nnodesRef - 1);
}
void MeshSideRefinement::correctRefFactor()
{
	refFactor = power_ceil(refFactor);
}
void MeshSideRefinement::normElementSizeAndNumbersFromRefFactor(double lengthx)
{
	elsizeNorm = (double)refFactor * elsizeRef;
	nnodesNorm = (int)(lengthx / elsizeNorm) + 1;
}

void MeshSideRefinement::calculateMeshSectionRefToNormLength()
{
	l_ref_to_norm = 0.0;
	int n = 1;
	while (n < refFactor) {
		l_ref_to_norm += 3.0*elsizeRef*(double)n;
		n *= 2;
	}
}

void MeshSideRefinement::calculateMeshSectionLengths(double lengthy)
{
	l_ref = (double)(refRows - 1) * elsizeRef;
	calculateMeshSectionRefToNormLength();
	if (l_ref_to_norm > (lengthy - l_ref)) {	
		yfac = (lengthy - l_ref) / l_ref_to_norm;

		l_norm   = 0.0;
		normRows = 0;
		elsizeNormY = 0.0;
		l_ref_to_norm *= yfac;
	}
	else {
		l_norm = lengthy - l_ref - l_ref_to_norm;

		normRows = (int)(l_norm / elsizeNorm);
		elsizeNormY = l_norm / (double)(normRows);
	}
}