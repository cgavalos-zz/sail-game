#pragma once

#include "Line.h"
#include <glm/glm.hpp>
#include <utility>

class Plane
{
private:
	glm::vec3 _point_on_plane;
	glm::vec3 _normal;
public:
    enum LineIntersect { 
        ONE_INTERSECT, 
        NO_INTERSECT, 
        LINE_IN_PLANE };
	Plane();
	Plane(
        glm::vec3 const & point_on_plane,
		glm::vec3 const & normal);
    // Positive distance is in direction of normal.
    glm::vec3
        getPoint() const;
    glm::vec3
        getNormal() const;
    void
        setPoint(glm::vec3 const & point_on_plane);
    void
        setNormal(glm::vec3 const & normal);
    float 
        distanceTo(glm::vec3 const & point) const;
    std::pair<glm::vec3, LineIntersect> 
        lineIntersect(Line const & line) const;
    bool 
        pointAbove(
            glm::vec3 const & point,
            glm::vec3 const & up) const;
};
