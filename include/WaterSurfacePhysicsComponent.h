#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <functional>
#include "Player.h"
#include "Plane.h"

class WaterSurfacePhysicsComponent {
private:
	const size_t verticesPerTriangle = 3;
	const size_t trianglesPerUnit = 2;
	const float density = 1000.0f; // kg/m^3
	const float gravity = 9.8f; // m/s^2

	size_t verticesPerSide;
	size_t numUnits;
	size_t numTris;
	size_t gridUnitsPerSide;
	float gridWidth;
	float unitSize;

    std::vector<glm::vec2> _gridPoints;
	std::vector<float> heights;
	glm::mat4 modelMatrix;
	std::function<float(glm::vec3 const &)> pressureLambda;
public:
	WaterSurfacePhysicsComponent(size_t _gridUnitsPerSide, float _gridWidth);
	void update(std::function<void(std::vector<float> const &)> const & updateFunction, Player const & player);
	void updateModelMatrix(Player const & player);

	float pressure(glm::vec3 const & position) const;
	
	size_t getNumHeights() const;
	size_t getNumHeightsPerSide() const;
	size_t getNumGridUnitsPerSide() const;
	size_t getNumElements() const;
	float const * getHeightDataPointer() const;
	std::vector<float> const & getHeightVector() const;

	float getUnitSize() const;
	glm::mat4 const & getModelMatrix() const;
	std::function<float(glm::vec3 const &)> const & getPressureLambda() const;

    Plane getPlane(glm::vec3 const & point) const;
};
