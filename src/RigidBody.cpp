#include "RigidBody.h"

#include <glm/gtc/matrix_transform.hpp>

RigidBody::RigidBody() {}

// Physics functions.
void RigidBody::step(float timeStep) {
  linStep(timeStep);
  rotStep(timeStep);
}

void RigidBody::linStep(float timeStep) {
  if (timeStep != 0.0f) {
    glm::vec3 acceleration = _sumForce / timeStep;
    _sumForce = glm::vec3();

    _velocity += acceleration * timeStep;

    _position += _velocity * timeStep;
  }
}

void RigidBody::rotStep(float timeStep) {
  if (timeStep != 0.0f) {
    glm::vec3 angularAcceleration =
        _inverseInertialTensor *
        (_sumMoment -
         glm::cross(_angularVelocity, _inertialTensor * _angularVelocity));

    _angularVelocity += angularAcceleration * timeStep;

    float magnitudeAngularVelocity = glm::length(_angularVelocity);
    glm::vec3 directionAngularVelocity =
        _angularVelocity / magnitudeAngularVelocity;
    float changeInAngle = magnitudeAngularVelocity * timeStep;
    glm::mat3 metaRotationMatrix = glm::mat3(
        glm::rotate(glm::mat4(1.0f), changeInAngle, directionAngularVelocity));

    _rotationMatrix = metaRotationMatrix * _rotationMatrix;
  }
}

void RigidBody::applyForce(glm::vec3 const &force) { _sumForce += force; }

void RigidBody::applyMoment(glm::vec3 const &moment) { _sumMoment += moment; }

void RigidBody::applyPointForce(PointForce const &pointForce) {
  applyPointForces(std::vector<PointForce>({pointForce}));
}

void RigidBody::applyPointForces(std::vector<PointForce> const &pointForces) {
  glm::vec3 forceSum;
  glm::vec3 momentSum;

  for (PointForce tempPointForce : pointForces) {
    glm::vec3 tempForce =
        tempPointForce.getDirection() * tempPointForce.getMagnitude();
    forceSum += tempForce;
    glm::vec3 momentArm = tempPointForce.getPoint() - _position;
    glm::vec3 tempMoment = glm::cross(momentArm, tempForce);
    momentSum += tempMoment;
  }

  applyForce(forceSum);
  applyMoment(momentSum);
}

// Getters
float RigidBody::getMass() const { return _mass; }

glm::vec3 RigidBody::getPosition() const { return _position; }

glm::vec3 RigidBody::getVelocity() const { return _velocity; }

glm::vec3 RigidBody::getCenterOfMass() const { return _centerOfMass; }

glm::vec3 RigidBody::getAngularVelocity() const { return _angularVelocity; }

glm::mat3 RigidBody::getRotationMatrix() const { return _rotationMatrix; }

glm::mat3 RigidBody::getInertialTensor() const { return _inertialTensor; }

glm::mat3 RigidBody::getInverseInertialTensor() const {
  return _inverseInertialTensor;
}

glm::mat4 RigidBody::getModelMatrix() const {
  glm::mat4 trans2 = glm::translate(glm::mat4(1.0f), _position);
  glm::mat4 trans1 = glm::translate(glm::mat4(1.0f), -_centerOfMass);
  return trans2 * glm::mat4(_rotationMatrix) * trans1;
}

// Setters
void RigidBody::setMass(float mass) { _mass = mass; }

void RigidBody::setPosition(glm::vec3 const &position) { _position = position; }

void RigidBody::setVelocity(glm::vec3 const &velocity) { _velocity = velocity; }

void RigidBody::setCenterOfMass(glm::vec3 const &centerOfMass) {
  _centerOfMass = centerOfMass;
}

void RigidBody::setAngularVelocity(glm::vec3 const &angularVelocity) {
  _angularVelocity = angularVelocity;
}

void RigidBody::setRotationMatrix(glm::mat3 const &rotationMatrix) {
  _rotationMatrix = rotationMatrix;
}

void RigidBody::setInertialTensor(glm::mat3 const &inertialTensor) {
  _inertialTensor = inertialTensor;
  _inverseInertialTensor = glm::inverse(_inertialTensor);
}

/*void RigidBody::setInverseInertialTensor(glm::mat3 const &
inverseInertialTensor)
{
    _inverseInertialTensor = inverseInertialTensor;
}*/

/*void RigidBody::setModelMatrix(glm::mat4 const & modelMatrix)
{
    _modelMatrix = modelMatrix;
}*/
