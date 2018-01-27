#pragma once

#include <glm/glm.hpp>

#include "Player.h"
#include "WaterSurface.h"
#include "WindowParameters.h"
#include "SkyParameters.h"
#include "RigidObject.h"
#include "SkyboxObject.h"
#include "UBOManager.h"
#include "TestObject.h"

class World {
private:
	const unsigned int gridUnitsPerSide = 40;
	const float gridWidth = 1000.0f;
	const float fovy = glm::radians(45.0f);
	const float zNear = 1.0f;
	const float sunAngularWidth = glm::radians(1.0f);
	const glm::vec3 sunPosition = glm::normalize(glm::vec3(0.0f, 1.0f, -15.0f));

	Player player;
	WaterSurface waterSurface;
	WindowParameters windowParameters;
	SkyParameters skyParameters;
	RigidObject buoyantObject;
	SkyboxObject skyboxObject;
	UBOManager manager;
public:
	World(unsigned int width, unsigned int height, SDL_Event * e);
	void update(float timeStep);
};
