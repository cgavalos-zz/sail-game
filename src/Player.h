#pragma once

#include "Camera.h"
#include "PlayerInputComponent.h"

class Player {
private:
	Camera camera;
	PlayerInputComponent input;
public:
	Player(SDL_Event * e);
	void update();
	Camera const & getCamera() const;
};