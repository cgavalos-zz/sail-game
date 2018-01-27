#pragma once

#include <SDL2/SDL.h>
#include "Camera.h"

class PlayerInputComponent {
private:
	SDL_Event * e;
	bool held;
	bool mouseCaptured;
public:
	PlayerInputComponent(SDL_Event * _e);
	void update(Camera & camera);
};
