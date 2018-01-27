#pragma once

#include "SkyboxObjectGraphicsComponent.h"

class SkyboxObject {
private:
	SkyboxObjectGraphicsComponent sogc;
public:
	void update() const;
};