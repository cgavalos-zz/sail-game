#pragma once

#include "RigidObjectGraphicsComponent.h"
#include "RigidObjectPhysicsComponent.h"


class RigidObject {
private:
	RigidObjectPhysicsComponent ropc;
	RigidObjectGraphicsComponent rogc;
public:
	RigidObject(
		std::vector<glm::vec3> const & vertices,
		std::vector<unsigned int> const & elements);
	RigidObjectGraphicsComponent const & getGraphicsComponent() const;
	void update(WaterSurface const & waterSurface, float timeStep);
	static RigidObject fromDataFile(std::string const & filename);
};
