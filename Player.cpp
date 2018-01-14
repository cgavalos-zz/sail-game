#include "Player.h"

Player::Player(SDL_Event * e) : input(e) {}

void Player::update() {
	input.update(camera);
}

Camera const & Player::getCamera() const {
	return camera;
}