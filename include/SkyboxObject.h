#pragma once

#include "PaintableObject.h"
#include "SkyboxObjectGraphicsComponent.h"

class SkyboxObject : public PaintableObject {
private:
  SkyboxObjectGraphicsComponent sogc;

public:
  void update() const;
};
