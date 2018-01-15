#include "World.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

World::World ( unsigned int width, unsigned int height, SDL_Event * e ) :
    player ( e ),
    waterSurface ( gridUnitsPerSide, gridWidth ),
    windowParameters ( fovy, width, height, zNear ),
    skyParameters ( sunPosition, sunAngularWidth ),
    buoyantObject ( RigidObject::fromDataFile ( "box2.txt" ) ),
    skyboxObject(),
    manager() {}

void World::update ( float timeStep ) {

    // Must be called first to fill UBOs.
    manager.update ( player, skyParameters, windowParameters );

    skyboxObject.update();
    player.update();
    waterSurface.update ( player );
    buoyantObject.update ( waterSurface, timeStep );

    TestObject to;
    to.update();

    player.getCamera();
}
