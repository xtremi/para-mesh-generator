#pragma once
#include "Mesh3D.h"
#include "MeshCircularRefinement3D.h"

class Mesh3DTubeRefFace 
   : public Mesh3D, public MeshCircularRefinement3D
{
public:
   Mesh3DTubeRefFace(const glm::dvec3& _pos, double _radInner, double _radOuter, double _height, double _elsizeRef, double _elSizeNorm, int _refRows, double _revAng = -1.0);
};

