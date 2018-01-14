#pragma once

#include <glm/glm.hpp>
#include "WaterSurface.h"

class RigidObjectPhysicsComponent {
private:
	float mass;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 com;
	glm::vec3 omega;
	glm::mat3 rotM;
	glm::mat3 I;
	glm::mat3 invI;

	float maxCalcArea;

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> elements;
	glm::mat4 modelMatrix;
public:
	RigidObjectPhysicsComponent(
		std::vector<glm::vec3> const & _vertices,
		std::vector<unsigned int> const & _elements,
		float _maxCalcArea);
	glm::mat4 const & getModelMatrix() const;
	void updateModelMatrix();
	void update(WaterSurface const & waterSurface, float timeStep);
	void pointForces(std::vector<PointForce> const & pfs, float timeStep);
	void pointForce(PointForce const & pf, float timeStep);
	void force(glm::vec3 const & f, float timeStep);
	void moment(glm::vec3 const & M, float timeStep);
	void linStep(float timeStep);
	void rotStep(float timeStep);
	void step(float timeStep);
};
