#include "Plane.h"

Plane::Plane() {
    Plane(
        glm::vec3(),
        glm::vec3());
}

Plane::Plane(
    glm::vec3 const & point_on_plane,
    glm::vec3 const & normal) :
    _point_on_plane(point_on_plane),
    _normal(normal) {}

glm::vec3
Plane::getPoint() const {
    return _point_on_plane;
}

glm::vec3
Plane::getNormal() const {
    return _normal;
}

void
Plane::setPoint(glm::vec3 const & point_on_plane) {
    _point_on_plane = point_on_plane;
}

void
Plane::setNormal(glm::vec3 const & normal) {
    _normal = normal;
}

std::pair<glm::vec3, Plane::LineIntersect>
Plane::lineIntersect(Line const & line) const {
    glm::vec3 l = line.getDirection();
    glm::vec3 l0 = line.getPoint();
    glm::vec3 n = _normal;
    glm::vec3 p0 = _point_on_plane;

    float bottom = glm::dot(l, n);
    float top = glm::dot((p0 - l0), n);
    float zero = 0.0f;
    LineIntersect type;
    glm::vec3 intersect;

    if (bottom == zero) {
        if (top == zero) {
            type = NO_INTERSECT;
        }
        else {
            type = LINE_IN_PLANE;
            intersect = l0;
        }
    }
    else {
        type = ONE_INTERSECT;
        intersect = l * (top / bottom) + l0;
    }

    return std::make_pair(intersect, type);
}

bool
Plane::pointAbove(
    glm::vec3 const & point,
    glm::vec3 const & up) const {
    return glm::dot(point - _point_on_plane, _normal) * glm::dot(_normal, up) > 0;
}

float
Plane::distanceTo(glm::vec3 const & point) const {
    return glm::dot(point - _point_on_plane, _normal);
}
