#pragma once

#include <glm/glm.hpp>
#include <vector>

class PointForce {
private:
    glm::vec3 _point;
    glm::vec3 _direction;
    float _magnitude;
public:
    PointForce();
    PointForce (
        glm::vec3 const & point,
        glm::vec3 const & direction,
        float force );
    void setPoint ( glm::vec3 const & point );
    void setDirection ( glm::vec3 const & direction );
    void setMagnitude ( float magnitude );
    glm::vec3 getPoint() const;
    glm::vec3 getDirection() const;
    float getMagnitude() const;
    static PointForce codirectionalWeightedSum (std::vector<PointForce> const & forces);
};
