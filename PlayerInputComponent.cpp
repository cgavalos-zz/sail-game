#include "PlayerInputComponent.h"

PlayerInputComponent::PlayerInputComponent(SDL_Event * _e) {
	e = _e;
	held = false;
	mouseCaptured = false;
}

void PlayerInputComponent::update(Camera & camera) {

	float speed = 0.25f;
	float pitchSpeed = 1.0f / 1000.0f;
	float yawSpeed = 1.0f / 1000.0f;

	const Uint8 * keyboardState = SDL_GetKeyboardState(NULL);

	float pitchAng = camera.getPitch();
	float yawAng = camera.getYaw();

	pitchAng += (keyboardState[SDL_SCANCODE_UP] - keyboardState[SDL_SCANCODE_DOWN]) * pitchSpeed;
	yawAng += (keyboardState[SDL_SCANCODE_LEFT] - keyboardState[SDL_SCANCODE_RIGHT]) * yawSpeed;

	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		if (!held) {
			mouseCaptured = !mouseCaptured;
			if (mouseCaptured) {
				SDL_SetRelativeMouseMode(SDL_TRUE);
			}
			else {
				SDL_SetRelativeMouseMode(SDL_FALSE);
			}
		}
		held = true;
	}
	else {
		held = false;
	}

	if (mouseCaptured) {
		if ((*e).type == SDL_MOUSEMOTION) {
			int xrel;
			int yrel;
			SDL_GetRelativeMouseState(&xrel, &yrel);
			yawAng -= xrel * yawSpeed;
			pitchAng -= yrel * pitchSpeed;
		}
	}

	if (keyboardState[SDL_SCANCODE_W]) {
		camera.setPosition(camera.getPosition() + camera.getForward() * speed);
	}
	if (keyboardState[SDL_SCANCODE_S]) {
		camera.setPosition(camera.getPosition() - camera.getForward() * speed);
	}
	if (keyboardState[SDL_SCANCODE_A]) {
		camera.setPosition(camera.getPosition() - camera.getRight() * speed);
	}
	if (keyboardState[SDL_SCANCODE_D]) {
		camera.setPosition(camera.getPosition() + camera.getRight() * speed);
	}
	if (keyboardState[SDL_SCANCODE_SPACE]) {
		camera.setPosition(camera.getPosition() + camera.getUp() * speed);
	}
	if (keyboardState[SDL_SCANCODE_C]) {
		camera.setPosition(camera.getPosition() - camera.getUp() * speed);
	}

	camera.setAngles(pitchAng, yawAng, 0.0f);
}