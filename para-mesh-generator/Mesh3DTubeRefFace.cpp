#pragma once
#include "Mesh3DTubeRefFace.h"

Mesh3DTubeRefFace::Mesh3DTubeRefFace(const glm::dvec3& _pos, double _radInner, double _radOuter, double _height, double _elsizeRef, double _elSizeNorm, int _refRows, double _revAng)
   :Mesh3D(_pos), MeshCircularRefinement3D(glm::dvec3(), _refRows, _elSizeNorm, _elsizeRef)
{

}