#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "Object.h"
#include "ObjectPainter.h"
#include "PaintableObject.h"
#include "Painter.h"

class World {
private:
  std::vector<std::shared_ptr<Object>> nonPaintableObjects;

  std::vector<std::shared_ptr<Painter>> otherPainters;

  std::vector<std::shared_ptr<PaintableObject>> paintableObjects;
  std::vector<std::shared_ptr<ObjectPainter>> objectPainters;

public:
  void paintUpdate();
  void physicsUpdate(float timeStep);
  void update(float timeStep);
  void addNonPaintableObject(std::shared_ptr<Object> object);
  void addPaintableObject(std::shared_ptr<PaintableObject> object);
  void addOtherPainter(std::shared_ptr<Painter> painter);
  void addObjectPainter(std::shared_ptr<ObjectPainter> painter);
};

#endif
