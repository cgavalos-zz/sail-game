#include "RigidObject.h"
#include "ShaderMisc.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void RigidObject::update(float timeStep) {
  // TODO Write stuff.
  // m_body.step(timeStep);
  vegc.use(program);
  glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE,
                     glm::value_ptr(glm::mat4(1.0f)));
  vegc.draw();
}

void RigidObject::setMesh(Mesh mesh) {
  m_mesh = mesh;
  std::vector<Triangle> triangles = m_mesh.getTriangles();
  std::vector<glm::vec3> vertices;
  std::vector<GLuint> elements;
  for (Triangle t : triangles) {
    elements.push_back(vertices.size());
    vertices.push_back(t.v1g());
    elements.push_back(vertices.size());
    vertices.push_back(t.v2g());
    elements.push_back(vertices.size());
    vertices.push_back(t.v3g());
  }
  vegc = VertexElementGraphicsComponent(vertices, elements);

  std::vector<GLenum> types({GL_VERTEX_SHADER, GL_FRAGMENT_SHADER});

  std::vector<std::string> filenames(
      {"glsl/buoyantVert.glsl", "glsl/buoyantFrag.glsl"});

  program = programSetup(types, filenames);
  glUseProgram(program);

  GLuint pLoc = glGetAttribLocation(program, "position");

  glEnableVertexAttribArray(pLoc);
  glVertexAttribPointer(pLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void RigidObject::setRigidBody(RigidBody body) { m_body = body; }
