#include "WaterSurfacePhysicsComponent.h"

#include <glm/gtc/matrix_transform.hpp>

WaterSurfacePhysicsComponent::WaterSurfacePhysicsComponent(
	size_t _gridUnitsPerSide,
	float _gridWidth) :
	heights(),
	pressureLambda([this](glm::vec3 v){
		return this->pressure(v); }) {

	gridWidth = _gridWidth;
	gridUnitsPerSide = _gridUnitsPerSide;
	unitSize = gridWidth / gridUnitsPerSide;

	gridUnitsPerSide = _gridUnitsPerSide;
	numUnits = gridUnitsPerSide * gridUnitsPerSide;
	numTris = numUnits * trianglesPerUnit;
	verticesPerSide = gridUnitsPerSide + 1;
	auto numVertices = verticesPerSide * verticesPerSide;

	heights.resize(numVertices);
    // generate gridPoints.
}

void WaterSurfacePhysicsComponent::update(
	std::function<void(std::vector<float> const &)> const & updateFunction,
	Player const & player) {

	updateModelMatrix(player);
	updateFunction(heights);
}

size_t WaterSurfacePhysicsComponent::getNumHeights() const {
	return heights.size();
}

std::vector<float> const & WaterSurfacePhysicsComponent::getHeightVector() const {
	return heights;
}

size_t WaterSurfacePhysicsComponent::getNumHeightsPerSide() const {
	return verticesPerSide;
}

float const * WaterSurfacePhysicsComponent::getHeightDataPointer() const {
	return heights.data();
}

size_t WaterSurfacePhysicsComponent::getNumGridUnitsPerSide() const {
	return gridUnitsPerSide;
}

size_t WaterSurfacePhysicsComponent::getNumElements() const {
	return numTris * verticesPerTriangle;
}

float WaterSurfacePhysicsComponent::getUnitSize() const {
	return unitSize;
}

void WaterSurfacePhysicsComponent::updateModelMatrix(Player const & player) {

	glm::mat4 rot = glm::rotate(
		glm::mat4(1.0f),
		glm::radians(90.0f),
		glm::vec3(-1, 0, 0));
	glm::mat4 scale = glm::scale(
		glm::mat4(1.0f),
		glm::vec3(unitSize, unitSize, unitSize));
	glm::vec3 pos = player.getCamera().getPosition();

	int nx = (int)(pos.x / unitSize);

	if (pos.x < 0) {
		nx -= 1;
	}

	int nz = (int)(pos.z / unitSize);

	if (pos.z < 0) {
		nz -= 1;
	}

	nx -= gridUnitsPerSide / 2;
	nz += gridUnitsPerSide / 2;

	glm::vec3 tvec = glm::vec3((float)nx, 0.0f, (float)nz) * unitSize;
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), tvec);

	modelMatrix = translate * scale * rot;
}

glm::mat4 const & WaterSurfacePhysicsComponent::getModelMatrix() const {
	return modelMatrix;
}

// Does not work for non-flat.
float WaterSurfacePhysicsComponent::pressure(glm::vec3 const & position) const {

	float y = position.y;
	if (y > 0) {
		y = 0;
	}

	return density * gravity * -y;
}

std::function<float(glm::vec3 const &)> const &
WaterSurfacePhysicsComponent::getPressureLambda() const {
	return pressureLambda;
}

Plane
WaterSurfacePhysicsComponent::getPlane(glm::vec3 const & point) const {
    return Plane(glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
}
