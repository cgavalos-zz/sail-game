#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "PointForce.h"

class RigidObject
{
private:
    float _mass;
    glm::vec3 _position;
    glm::vec3 _velocity;
    glm::vec3 _centerOfMass;
    glm::vec3 _angularVelocity;
    glm::mat3 _rotationMatrix;
    glm::mat3 _inertialTensor;
    glm::mat3 _inverseInertialTensor;

    glm::vec3 _sumForce;
    glm::vec3 _sumMoment;
protected:
public:
    RigidObject();

    // Physics functions.
    void step(float timeStep);
    void linStep(float timeStep);
    void rotStep(float timeStep);
    void applyForce(glm::vec3 const & force);
    void applyMoment(glm::vec3 const & moment);
    void applyPointForce(PointForce const & pointForce);
    void applyPointForces(std::vector<PointForce> const & pointForces);

    // Getters
    float getMass() const;
    glm::vec3 getPosition() const;
    glm::vec3 getVelocity() const;
    glm::vec3 getCenterOfMass() const;
    glm::vec3 getAngularVelocity() const;
    glm::mat3 getRotationMatrix() const;
    glm::mat3 getInertialTensor() const;
    glm::mat3 getInverseInertialTensor() const;
    glm::mat4 getModelMatrix() const;

    // Setters
    void setMass(float mass);
    void setPosition(glm::vec3 const & position);
    void setVelocity(glm::vec3 const & velocity);
    void setCenterOfMass(glm::vec3 const & centerOfMass);
    void setAngularVelocity(glm::vec3 const & angularVelocity);
    void setRotationMatrix(glm::mat3 const & rotationMatrix);
    void setInertialTensor(glm::mat3 const & inertialTensor);
    //void setInverseInertialTensor(glm::mat3 const & inverseInertialTensor);
    //void setModelMatrix(glm::mat4 const & modelMatrix);
};
