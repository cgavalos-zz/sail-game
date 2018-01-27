#include "RigidObject.h"

#include <glm/gtc/matrix_transform.hpp>

RigidObject::RigidObject() {}

// Physics functions.
void RigidObject::step(float timeStep)
{
    linStep(timeStep);
    rotStep(timeStep);
}

void RigidObject::linStep(float timeStep)
{
    if (timeStep != 0.0f)
    {
        glm::vec3 acceleration = _sumForce / timeStep;
        _sumForce = glm::vec3();

        _velocity += acceleration * timeStep;

        _position += _velocity * timeStep;
    }
}

void RigidObject::rotStep(float timeStep)
{
    if (timeStep != 0.0f)
    {
        glm::vec3 angularAcceleration =
            _inverseInertialTensor *
            (_sumMoment - glm::cross(
                _angularVelocity,
                _inertialTensor * _angularVelocity));

        _angularVelocity += angularAcceleration * timeStep;

        float magnitudeAngularVelocity = glm::length(_angularVelocity);
        glm::vec3 directionAngularVelocity = _angularVelocity / magnitudeAngularVelocity;
        float changeInAngle = magnitudeAngularVelocity * timeStep;
        glm::mat3 metaRotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0f), changeInAngle, directionAngularVelocity));

        _rotationMatrix = metaRotationMatrix * _rotationMatrix;
    }
}

void RigidObject::applyForce(glm::vec3 const & force)
{
    _sumForce += force;
}

void RigidObject::applyMoment(glm::vec3 const & moment)
{
    _sumMoment += moment;
}

void RigidObject::applyPointForce(PointForce const & pointForce)
{
    applyPointForces(std::vector<PointForce>({pointForce}));
}

void RigidObject::applyPointForces(std::vector<PointForce> const & pointForces)
{
    glm::vec3 forceSum;
    glm::vec3 momentSum;

    for (PointForce tempPointForce : pointForces)
    {
        glm::vec3 tempForce =
            tempPointForce.getDirection() *
            tempPointForce.getMagnitude();
        forceSum += tempForce;
        glm::vec3 momentArm = tempPointForce.getPoint() - _position;
        glm::vec3 tempMoment = glm::cross(momentArm, tempForce);
        momentSum += tempMoment;
    }

    applyForce(forceSum);
    applyMoment(momentSum);
}

// Getters
float RigidObject::getMass() const
{
    return _mass;
}

glm::vec3 RigidObject::getPosition() const
{
    return _position;
}

glm::vec3 RigidObject::getVelocity() const
{
    return _velocity;
}

glm::vec3 RigidObject::getCenterOfMass() const
{
    return _centerOfMass;
}

glm::vec3 RigidObject::getAngularVelocity() const
{
    return _angularVelocity;
}

glm::mat3 RigidObject::getRotationMatrix() const
{
    return _rotationMatrix;
}

glm::mat3 RigidObject::getInertialTensor() const
{
    return _inertialTensor;
}

glm::mat3 RigidObject::getInverseInertialTensor() const
{
    return _inverseInertialTensor;
}

glm::mat4 RigidObject::getModelMatrix() const
{
    glm::mat4 trans2 =
        glm::translate(
            glm::mat4(1.0f),
            _position);
    glm::mat4 trans1 =
        glm::translate(
            glm::mat4(1.0f),
            -_centerOfMass);
    return trans2 * glm::mat4(_rotationMatrix) * trans1;
}

// Setters
void RigidObject::setMass(float mass)
{
    _mass = mass;
}

void RigidObject::setPosition(glm::vec3 const & position)
{
    _position = position;
}

void RigidObject::setVelocity(glm::vec3 const & velocity)
{
    _velocity = velocity;
}

void RigidObject::setCenterOfMass(glm::vec3 const & centerOfMass)
{
    _centerOfMass = centerOfMass;
}

void RigidObject::setAngularVelocity(glm::vec3 const & angularVelocity)
{
    _angularVelocity = angularVelocity;
}

void RigidObject::setRotationMatrix(glm::mat3 const & rotationMatrix)
{
    _rotationMatrix = rotationMatrix;
}

void RigidObject::setInertialTensor(glm::mat3 const & inertialTensor)
{
    _inertialTensor = inertialTensor;
    _inverseInertialTensor = glm::inverse(_inertialTensor);
}

/*void RigidObject::setInverseInertialTensor(glm::mat3 const & inverseInertialTensor)
{
    _inverseInertialTensor = inverseInertialTensor;
}*/

/*void RigidObject::setModelMatrix(glm::mat4 const & modelMatrix)
{
    _modelMatrix = modelMatrix;
}*/
