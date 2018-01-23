#include "PointForce.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

PointForce::PointForce()
{
    PointForce (
        glm::vec3(),
        glm::vec3(),
        0.0f);
}

PointForce::PointForce (
    glm::vec3 const & point,
    glm::vec3 const & direction,
    float magnitude) :
    _point (point),
    _direction (direction),
    _magnitude (magnitude) {}

void
PointForce::setPoint (glm::vec3 const & point)
{
    _point = point;
}

void
PointForce::setDirection (glm::vec3 const & direction)
{
    _direction = direction;
}

void
PointForce::setMagnitude (float magnitude)
{
    _magnitude = magnitude;
}

glm::vec3
PointForce::getPoint() const
{
    return _point;
}

glm::vec3
PointForce::getDirection() const
{
    return _direction;
}

float
PointForce::getMagnitude() const
{
    return _magnitude;
}

PointForce
PointForce::codirectionalWeightedSum (std::vector<PointForce> const & forces)
{
    if (forces.size() > 0)
    {
        float magnitudeSum = 0.0f;
        glm::vec3 pointSum;
        glm::vec3 direction;

        for (PointForce p : forces)
        {
            if (p.getMagnitude() != 0)
            {
                direction = p.getDirection();
            }
            float tempMagnitude = p.getMagnitude();
            magnitudeSum += tempMagnitude;
            pointSum += p.getPoint() * tempMagnitude;
        }

        if (magnitudeSum == 0.0f)
        {
            return PointForce (pointSum, direction, magnitudeSum);
        }
        else
        {
            return PointForce (pointSum / magnitudeSum, direction, magnitudeSum);
        }
    }
    else
    {
        return PointForce();
    }
}

void PointForce::debug() const {
    std::cout << "Direction: " << glm::to_string(getDirection()) << std::endl;
    std::cout << "Point: " << glm::to_string(getPoint()) << std::endl;
    std::cout << "Magnitude: " << getMagnitude() << std::endl;
}
