#pragma once

#include "VertexElementGraphicsComponent.h"

class SkyboxObjectGraphicsComponent {
private:
	GLuint program;
	VertexElementGraphicsComponent vegc;
public:
	SkyboxObjectGraphicsComponent();
	void update() const;
};
