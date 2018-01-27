#include "InitWorld.h"

#include <memory>

#include "SkyboxObject.h"
#include "SkyboxPainter.h"

void initWorld(World *world) {
  std::shared_ptr<SkyboxObject> skybox = std::make_shared<SkyboxObject>();
  std::shared_ptr<SkyboxPainter> painter =
      std::make_shared<SkyboxPainter>(skybox);
  world->addPaintableObject(skybox);
  world->addObjectPainter(skyboxPainter);
}
