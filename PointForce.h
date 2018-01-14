#pragma once

#include <glm/glm.hpp>

typedef struct {
	glm::vec3 point;
	float force;
	glm::vec3 direction;
} PointForce;

PointForce fromParams(glm::vec3 point, float force, glm::vec3 direction);
