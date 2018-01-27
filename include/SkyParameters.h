#pragma once

#include <glm/glm.hpp>

class SkyParameters {
private:
	glm::vec3 sunDirection;
	float dotAngle;
	float sunAngularDiameter;
public:
	SkyParameters (glm::vec3 const & _sunDirection, float _sunWidth);
	float getSunAngularDiameter() const;
	glm::vec3 const & getSunDirection() const;
	float getDotAngle() const;
};
