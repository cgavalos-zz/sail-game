#ifndef RIGID_OBJECT_H
#define RIGID_OBJECT_H

#include "Mesh.h"
#include "RigidBody.h"
#include "VertexElementGraphicsComponent.h"

class RigidObject {
private:
  GLuint program;
  Mesh m_mesh;
  RigidBody m_body;
  VertexElementGraphicsComponent vegc;

public:
  // RigidObject();
  void setMesh(Mesh mesh);
  void setRigidBody(RigidBody body);
  void update(float timeStep);
};

#endif
