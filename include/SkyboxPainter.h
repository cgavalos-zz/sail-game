#ifndef SKYBOX_PAINTER_H
#define SKYBOX_PAINTER_H

#include "ObjectPainter.h"
#include "SkyboxObject.h"

class SkyboxPainter : protected ObjectPainter {
private:
  std::shared_ptr<SkyboxObject> m_skybox;

public:
  SkyboxPainter(std::shared_ptr<SkyboxObject> skybox);
  void paintUpdate();
};

#endif
