#pragma once

#include <glm/glm.hpp>

class Line
{
private:
	glm::vec3 _point_on_line;
	glm::vec3 _direction;
public:
	Line();
	Line(glm::vec3 point_on_line, 
		 glm::vec3 direction);
	glm::vec3 getPoint() const;
	glm::vec3 getDirection() const;
	void setPoint(glm::vec3 point_on_line);
	void setDirection(glm::vec3 direction);
};
