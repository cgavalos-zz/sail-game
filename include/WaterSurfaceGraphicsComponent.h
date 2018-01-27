#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>
#include <functional>

#include "VertexElementGraphicsComponent.h"

class WaterSurfaceGraphicsComponent {
private:
	GLint positionLoc;

	GLint modelLocation;
	GLint zLoc;
	GLint ab;
	GLint verticesPerSideLoc;
	GLint unitSizeLoc;
	
	GLuint program;
	std::vector<unsigned int> elementIndices;
	VertexElementGraphicsComponent vegc;
	std::function<void(std::vector<float> const &)> updateFunction;
public:
	WaterSurfaceGraphicsComponent(
		unsigned int numGridUnits,
		unsigned int numHeightsPerSide,
		unsigned int numElements,
		std::vector<float> const & heightVector,
		float unitSize);
	GLuint getProgram() const;
	void update(glm::mat4 const & modelM) const;
	VertexElementGraphicsComponent const & getGraphicsComponent() const;
	std::vector<unsigned int> generateElementVector(
		unsigned int gridUnitsPerSide,
		unsigned int verticesPerSide,
		unsigned int numElements) const;
	std::function<void(std::vector<float> const &)> const & getUpdateFunction() const;
};
