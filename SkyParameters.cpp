#include "SkyParameters.h"

SkyParameters::SkyParameters (glm::vec3 const & _sunDirection, float _sunWidth) {

	sunDirection = _sunDirection;
	sunAngularDiameter = _sunWidth;
	dotAngle = cosf(_sunWidth);
}

float SkyParameters::getSunAngularDiameter() const {
	return sunAngularDiameter;
}

glm::vec3 const & SkyParameters::getSunDirection() const {
	return sunDirection;
}

float SkyParameters::getDotAngle() const {
	return dotAngle;
}