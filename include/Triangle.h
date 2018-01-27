#pragma once

#include <glm/glm.hpp>
#include "Plane.h"
#include <vector>

class Triangle
{
private:
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;
    glm::vec3 normal;
    glm::vec3 center;
    float area;
public:
    enum PlaneStatus { ABOVE, BELOW, CROSS };

    Triangle();
    Triangle (
        glm::vec3 const & _v1,
        glm::vec3 const & _v2,
        glm::vec3 const & _v3);
    Triangle (
        glm::vec3 const & _v1,
        glm::vec3 const & _v2,
        glm::vec3 const & _v3,
        glm::vec3 const & _normal);
    Triangle (
        glm::vec3 const & _v1,
        glm::vec3 const & _v2,
        glm::vec3 const & _v3,
        glm::vec3 const & _normal,
        float _area);


    glm::vec3
    getCentroid() const;
    glm::vec3
    getNormal() const;
    float
    getArea() const;
    PlaneStatus
    partial_plane_status (
        Plane const & plane,
        glm::vec3 const & up) const;
    PlaneStatus
    plane_status (
        Plane const & plane,
        glm::vec3 const & up) const;
    std::pair<std::vector<Triangle>, std::vector<Triangle>>
            clip (
                Plane const & plane,
                glm::vec3 const & up) const;
    std::vector<Triangle>
    tessellate() const;
    Triangle transform(glm::mat4 const & matrix) const;
};
