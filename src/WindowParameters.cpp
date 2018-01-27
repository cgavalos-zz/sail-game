#include "WindowParameters.h"


#include <glm/gtc/matrix_transform.hpp>

WindowParameters::WindowParameters(
	float _fovy,
	unsigned int _width,
	unsigned int _height,
	float _zNear) {

	fovy = _fovy;
	width = _width;
	height = _height;
	zNear = _zNear;
	aspect = (float)width / (float)height;
	projectionM = glm::infinitePerspective(fovy, aspect, zNear);
	windowSize = glm::vec2((float)width, (float)height);
}

glm::mat4 const & WindowParameters::getProjectionMatrix() const {
	return projectionM;
}

float WindowParameters::getZNear() const {
	return zNear;
}

float WindowParameters::getFOVY() const {
	return fovy;
}

float WindowParameters::getAspectRatio() const {
	return aspect;
}

unsigned int WindowParameters::getWidth() const {
	return width;
}

unsigned int WindowParameters::getHeight() const {
	return height;
}

glm::vec2 const & WindowParameters::getWindowSize() const {
	return windowSize;
}
