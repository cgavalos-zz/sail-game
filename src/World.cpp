#include "World.h"

void World::paintUpdate() {
  for (auto painter : otherPainters) {
    painter->paintUpdate();
  }
  for (auto painter : objectPainters) {
    painter->paintUpdate();
  }
}

void World::physicsUpdate(float timeStep) {
  for (auto object : nonPaintableObjects) {
    object->physicsUpdate(timeStep);
  }
  for (auto object : paintableObjects) {
    object->physicsUpdate(timeStep);
  }
}

void World::update(float timeStep) {
  physicsUpdate(timeStep);
  paintUpdate();
}

void World::addNonPaintableObject(std::shared_ptr<Object> object) {
  nonPaintableObjects.push_back(object);
}

void World::addPaintableObject(std::shared_ptr<PaintableObject> object) {
  paintableObjects.push_back(object);
}

void World::addOtherPainter(std::shared_ptr<Painter> painter) {
  otherPainters.push_back(painter);
}

void World::addObjectPainter(std::shared_ptr<ObjectPainter> painter) {
  objectPainters.push_back(painter);
}
