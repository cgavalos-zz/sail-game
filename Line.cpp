#include "Line.h"

Line::Line() {
    Line(glm::vec3(),
         glm::vec3());
}

Line::Line(
    glm::vec3 point_on_line,
    glm::vec3 direction) :
    _point_on_line(point_on_line), 
    _direction(direction) {}

glm::vec3 Line::getPoint() const {
    return _point_on_line;
}

glm::vec3 Line::getDirection() const {
    return _direction;
}

void Line::setPoint(glm::vec3 point_on_line) {
    _point_on_line = point_on_line;
}

void Line::setDirection(glm::vec3 direction) {
    _direction = direction;
}