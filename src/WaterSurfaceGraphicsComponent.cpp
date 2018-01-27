#include "WaterSurfaceGraphicsComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderMisc.h"

#include "Player.h"

WaterSurfaceGraphicsComponent::WaterSurfaceGraphicsComponent(
	unsigned int gridUnitsPerSide,
	unsigned int numHeightsPerSide,
	unsigned int numElements,
	std::vector<float> const & heightVector,
	float unitSize) :
	elementIndices(
		generateElementVector(
			gridUnitsPerSide,
			numHeightsPerSide,
			numElements)),
	vegc(heightVector, elementIndices) {

	auto vBuffer = vegc.getVertexBuffer();

	updateFunction = [vBuffer](std::vector<float> const & v) {
		glNamedBufferSubData(vBuffer, 0, v.size(), v.data());
	};

	std::vector<GLenum> types({
		GL_VERTEX_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER });

	std::vector<std::string> filenames({
		"glsl/waterVert.glsl", "glsl/waterGeom.glsl", "glsl/waterFrag.glsl" });

	program = programSetup(types, filenames);
	glUseProgram(program);

	modelLocation = glGetUniformLocation(program, "model");
	ab = glGetUniformLocation(program, "allBlack");
	zLoc = glGetAttribLocation(program, "z");
	verticesPerSideLoc = glGetUniformLocation(program, "verticesPerSide");
	unitSizeLoc = glGetUniformLocation(program, "unitSize");

	glEnableVertexAttribArray(zLoc);
	glVertexAttribPointer(zLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glUniform1i(verticesPerSideLoc, numHeightsPerSide);
	glUniform1f(unitSizeLoc, unitSize);
}

GLuint WaterSurfaceGraphicsComponent::getProgram() const {
	return program;
}

void WaterSurfaceGraphicsComponent::update(glm::mat4 const & modelM) const {

	vegc.use(program);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelM));

	glPolygonMode(GL_FRONT, GL_FILL);
	glUniform1i(ab, 0);
	vegc.draw();

	glPolygonMode(GL_FRONT, GL_LINE);
	glUniform1i(ab, 1);
	vegc.draw();
	glPolygonMode(GL_FRONT, GL_FILL);
}

VertexElementGraphicsComponent const &
WaterSurfaceGraphicsComponent::getGraphicsComponent() const {
	return vegc;
}

std::vector<unsigned int>
WaterSurfaceGraphicsComponent::generateElementVector(
	unsigned int gridUnitsPerSide,
	unsigned int verticesPerSide,
	unsigned int numElements) const {

	std::vector<unsigned int> tempElementIndices(numElements);

	for (unsigned int x = 0; x < gridUnitsPerSide; x++) {

		for (unsigned int y = 0; y < gridUnitsPerSide; y++) {

			auto gridnum = x + y * gridUnitsPerSide;

			auto vi1 = (x + 0) + (y + 0) * verticesPerSide;
			auto vi2 = (x + 1) + (y + 0) * verticesPerSide;
			auto vi3 = (x + 1) + (y + 1) * verticesPerSide;
			auto vi4 = (x + 0) + (y + 1) * verticesPerSide;

			tempElementIndices[gridnum * 6 + 0] = vi1;
			tempElementIndices[gridnum * 6 + 1] = vi2;
			tempElementIndices[gridnum * 6 + 2] = vi3;
			tempElementIndices[gridnum * 6 + 3] = vi1;
			tempElementIndices[gridnum * 6 + 4] = vi3;
			tempElementIndices[gridnum * 6 + 5] = vi4;
		}
	}

	return tempElementIndices;
}

std::function<void(std::vector<float> const &)> const &
WaterSurfaceGraphicsComponent::getUpdateFunction() const {
	return updateFunction;
}
