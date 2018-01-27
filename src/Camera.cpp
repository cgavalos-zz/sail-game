#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

float Camera::clamp(float x, float min, float max) const {

	if (x < min) {
		return min;
	}
	else if (x > max) {
		return max;
	}
	else {
		return x;
	}
}

void Camera::recalculate() {

	glm::vec3 tempForward(0, 0, -1);
	glm::vec3 tempRight(1, 0, 0);
	glm::vec3 tempUp(0, 1, 0);

	glm::mat3 yawRot = glm::mat3(glm::rotate(glm::mat4(1.0f), yaw, tempUp));

	tempForward = yawRot * tempForward;
	tempRight = yawRot * tempRight;

	glm::mat3 pitchRot = glm::mat3(glm::rotate(glm::mat4(1.0f), pitch, tempRight));

	tempForward = pitchRot * tempForward;
	tempUp = pitchRot * tempUp;

	glm::mat3 rollRot = glm::mat3(glm::rotate(glm::mat4(1.0f), roll, tempForward));

	tempRight = rollRot * tempRight;
	tempUp = rollRot * tempUp;

	forward = tempForward;
	up = tempUp;
	right = tempRight;

	recalculateTransform();
}

void Camera::recalculateTransform() {

	transform = glm::lookAt(position, position + forward, up);
}

Camera::Camera() {

	setAngles(glm::vec3(0, 0, 0));
}

void Camera::setAngles(glm::vec3 pyr) {

	pitch = pyr.x; //clamp(pyr.x, -pitchRange, pitchRange);
	yaw = pyr.y;
	roll = pyr.z;
	recalculate();
}

void Camera::setAngles(float newPitch, float newYaw, float newRoll) {
	pitch = newPitch;
	yaw = newYaw;
	roll = newRoll;
	recalculate();
}

void Camera::setPosition(glm::vec3 _position) {

	position = _position;
	recalculateTransform();
}

glm::vec3 const & Camera::getForward() const {

	return forward;
}

glm::vec3 const & Camera::getUp() const {

	return up;
}

glm::vec3 const & Camera::getRight() const {

	return right;
}

float Camera::getPitch() const {
	return pitch;
}

float Camera::getYaw() const {
	return yaw;
}

float Camera::getRoll() const {
	return roll;
}

glm::vec3 Camera::getAngles() const {
	return glm::vec3(pitch, yaw, roll);
}

glm::vec3 const & Camera::getPosition() const {
	return position;
}

glm::mat4 const & Camera::getTransform() const {
	return transform;
}
