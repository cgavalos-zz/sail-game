#include "PointForce.h"

PointForce fromParams(glm::vec3 point, float force, glm::vec3 direction) {
	PointForce p = {point, force, direction};
	return p;
}