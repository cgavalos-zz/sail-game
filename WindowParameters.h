#pragma once

#include <glm/glm.hpp>

class WindowParameters {
private:
	float fovy;
	float aspect;
	unsigned int width;
	unsigned int height;
	float zNear;
	glm::mat4 projectionM;
	glm::vec2 windowSize;
public:
	WindowParameters(
		float _fovy,
		unsigned int _width,
		unsigned int _height,
		float _zNear);
	glm::mat4 const & getProjectionMatrix() const;
	float getZNear() const;
	float getFOVY() const;
	float getAspectRatio() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	glm::vec2 const & getWindowSize() const;
};
