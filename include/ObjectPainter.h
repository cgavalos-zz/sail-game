#ifndef OBJECT_PAINTER_H
#define OBJECT_PAINTER_H

#include <memory>

#include "PaintableObject.h"
#include "Painter.h"

class ObjectPainter : public Painter {
  virtual ~ObjectPainter() = 0;
};

#endif
