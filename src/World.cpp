#include "World.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

World::World(unsigned int width, unsigned int height, SDL_Event *e)
    : player(e), waterSurface(gridUnitsPerSide, gridWidth),
      windowParameters(fovy, width, height, zNear),
      skyParameters(sunPosition, sunAngularWidth),
      // buoyantObject ( RigidObject::fromDataFile ( "modelfiles/box1.txt" ) ),
      skyboxObject(), manager() {
  buoyantObject.setMesh(Mesh::fromDataFile("modelfiles/box1.txt"));
  // buoyantObject.setRigidBody()
}

void World::update(float timeStep) {

  // Must be called first to fill UBOs.
  manager.update(player, skyParameters, windowParameters);

  skyboxObject.update();
  player.update();
  waterSurface.update(player);
  buoyantObject.update(timeStep);

  TestObject to;
  to.update();

  player.getCamera();
}
