#ifndef PAINTER_H
#define PAINTER_H

class Painter {
public:
  virtual void paintUpdate() = 0;
  virtual ~Painter() = 0;
};

#endif
