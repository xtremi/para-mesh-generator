#pragma once
#include "MeshPrimitive.h"

void MeshPrimitive::setFirstNodeID(int id) {
	nodeID1 = id;
}
void MeshPrimitive::setFirstElementID(int id) {
	elementID1 = id;
}
void MeshPrimitive::moveX(double x){
	pos.x += x;
}
void MeshPrimitive::moveY(double y) {
	pos.y += y;
}
void MeshPrimitive::moveZ(double z) {
	pos.z += z;
}
void MeshPrimitive::move(const glm::vec3& v) {
	pos += v;
}

