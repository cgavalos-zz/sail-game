#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
  virtual void physicsUpdate(float timeStep) = 0;
  virtual ~Object() = 0;
};

#endif
