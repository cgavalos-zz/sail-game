#pragma once

#include <glm/glm.hpp>

class Camera {
private:
  float pitch;
  float yaw;
  float roll;
  const float pitchRange = glm::radians(89.9f);
  glm::vec3 forward;
  glm::vec3 right;
  glm::vec3 up;
  glm::vec3 position;
  glm::mat4 transform;

  float clamp(float x, float min, float max) const;
  void recalculate();
  void recalculateTransform();

public:
  Camera();
  void setAngles(glm::vec3 pyr);
  void setAngles(float newPitch, float newYaw, float newRoll);
  void setPosition(glm::vec3 _position);
  glm::vec3 const &getForward() const;
  glm::vec3 const &getUp() const;
  glm::vec3 const &getRight() const;
  float getPitch() const;
  float getYaw() const;
  float getRoll() const;
  glm::vec3 getAngles() const;
  glm::vec3 const &getPosition() const;
  glm::mat4 const &getTransform() const;
};
