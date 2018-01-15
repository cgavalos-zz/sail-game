#include "RigidObjectPhysicsComponent.h"

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "PointForce.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <chrono>

float quality(float x, float l, float h) {
	return (x - l) / (h - l);
}

float eval_q(float q, float l, float h) {
	return l + (h - l) * q;
}

float interp_table(float x, float xtable[], float ytable[], unsigned int n) {
	unsigned int nlower = 0;
	while (nlower < n - 1 && x > xtable[nlower + 1]) {
		nlower++;
	}
	return eval_q(quality(x, xtable[nlower], xtable[nlower + 1]), ytable[nlower], ytable[nlower + 1]);
}

float Cd_Sphere(float Re) {

	float xtable[] = { -1.0f, 3.0f, log10f(4.0f) + 5.0f, log10f(4.0f) + 5.0f, 7.0f, 8.0f };
	float ytable[] = { 250.0f, 0.4f, 0.4f, 0.1f, 0.4f, 0.4f };
	unsigned int n = 6;

	if (Re <= 0.0f) {
		return 0.0f;
	}
	else {
		float lRe = log10(Re);
		return interp_table(lRe, xtable, ytable, n);
	}
}

template <class T>
void print(T a) {
	std::cout << glm::to_string(a) << std::endl;
}

RigidObjectPhysicsComponent::RigidObjectPhysicsComponent(
	std::vector<glm::vec3> const & _vertices,
	std::vector<unsigned int> const & _elements,
	float _maxCalcArea) :
	//bo(_vertices, _elements, _maxCalcArea),
	position(0.0f, 2.0f, 0.0f),
	velocity(0.0f, 0.0f, 0.0f),
	omega(0.0f, 0.0f, 0.0f),
	rotM(1.0f),
	I(1.0f),
	invI(),
	vertices(_vertices),
	elements(_elements) {

	maxCalcArea = _maxCalcArea;

	auto w = 10.0f; // x
	auto d = 10.0f; // z
	auto h = 1.0f; // y
	mass = 100.0f * w * d * h;
	auto Ic1 = (1.0f / 12.0f) * mass * (d * d + h * h); // x
	auto Ic2 = (1.0f / 12.0f) * mass * (w * w + d * d); // y
	auto Ic3 = (1.0f / 12.0f) * mass * (w * w + h * h); // z
	I = glm::mat3(1.0f);
	I[0][0] = Ic1;
	I[1][1] = Ic2;
	I[2][2] = Ic3;
	invI = glm::inverse(I);

	com = glm::vec3(w / 2.0f, h / 2.0f, d / 2.0f);

	rotM = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f))) * rotM;

	updateModelMatrix();
}

glm::mat4 const & RigidObjectPhysicsComponent::getModelMatrix() const {
	return modelMatrix;
}

void RigidObjectPhysicsComponent::updateModelMatrix() {
	glm::mat4 trans2 = glm::translate(
		glm::mat4(1.0f),
		position);
	glm::mat4 trans1 = glm::translate(
		glm::mat4(1.0f),
		-com);
	modelMatrix = trans2 * glm::mat4(rotM) * trans1;
}

void RigidObjectPhysicsComponent::update(WaterSurface const & waterSurface, float timeStep) {

	//std::cout << glm::to_string(position) << std::endl;
	//std::cout << glm::to_string(rotM) << std::endl;
	//std::cout << glm::to_string(rotM) << std::endl;

	//float g = 9.8f;
	//glm::vec3 gv = glm::vec3(0.0f, -g, 0.0f);

	// Re
	float v = glm::length(velocity);
	float nu_water = 8.9e-4f;
	float nu_air = 1.81e-5f;
	float x = 1.0f;
	float Re_water = v * x / nu_water;
	float Re_air = v * x / nu_air;

	// Drag
	glm::vec3 d;
	if (v != 0) {
		d = velocity / v;
	}
	float rho_water = 1000.0f;
	float rho_air = 1.225f;
	float conv = 1.05f / 0.47f;
	float cd_water = Cd_Sphere(Re_water) * conv;
	float cd_air = Cd_Sphere(Re_air) * conv;
	float fractionAbove = 0.0f;

	if (position.y > 0.5f) {
		fractionAbove = 1.0f;
	}
	else if (position.y < -0.5f) {
		fractionAbove = 0.0f;
	}
	else {
		fractionAbove = position.y + 0.5f;
	}

	auto A = 10.0f * 10.0f;
	float fd_air = 0.5f * rho_air * v * v * cd_air * fractionAbove * A;
	float fd_water = 0.5f * rho_water * v * v * cd_water * (1.0f - fractionAbove) * A;

	//std::cout << "Fd (water): " << fd_water << " Fd (air): " << fd_air << std::endl;

	force(-d * (fd_air + fd_water), timeStep);

	// Gravity
	//force(gv * mass, timeStep);

	auto pLamb = waterSurface.getPhysicsComponent().getPressureLambda();

	// Water Pressure

	//auto t1 = std::chrono::high_resolution_clock::now();
	/*pointForces(
		bo.calcForces(
			maxCalcArea,
			pLamb,
			modelMatrix),
		timeStep);*/

	//auto t2 = std::chrono::high_resolution_clock::now();

	// Rotation Friction

	auto lOmega = glm::length(omega);
	auto dDrag = -omega / lOmega;
	auto lengthScale = 10.0f;
	auto areaScale = lengthScale * lengthScale;
	auto vAnalogue = lOmega * lengthScale;
	auto q = 0.5f * rho_water * vAnalogue * vAnalogue;
	auto factor = 1.0f;
	auto Cd = 0.4f;
	auto magn = factor * lengthScale * q * Cd * areaScale;
	moment(magn * dDrag, timeStep);

	//auto forceSize = 1000.0f;
	//PointForce pf = { glm::vec3(modelMatrix * glm::vec4(10.0f, 1.0f, 10.0f, 1.0f)), forceSize, glm::vec3(0.0f, -1.0f, 0.0f) };
	//pointForce(pf, timeStep);

	//std::cout << std::endl;
	//std::cout << "Calc Time (ms): " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1.0e6f << std::endl;
	//std::cout << lOmega << std::endl;
	step(timeStep);
	updateModelMatrix();
}

void RigidObjectPhysicsComponent::pointForces(
	std::vector<PointForce> const & pfs,
	float timeStep) {

	glm::vec3 forceSum;
	glm::vec3 momentSum;

	for (unsigned int i = 0; i < pfs.size(); i++) {

		auto cur = pfs.at(i);
		auto forceV = cur.force * cur.direction;
		forceSum += forceV;

		auto r = cur.point - position;
		auto M = glm::cross(r, forceV);
		momentSum += M;
	}

	force(glm::mat3(rotM) * forceSum, timeStep);
	moment(momentSum, timeStep);
}

void RigidObjectPhysicsComponent::pointForce(PointForce const & pf, float timeStep) {

	auto forceV = pf.direction * pf.force;
	force(glm::mat3(rotM) * forceV, timeStep);

	auto r = pf.point - position;
	auto M = glm::cross(r, forceV);
	moment(M, timeStep);
}

void RigidObjectPhysicsComponent::force(glm::vec3 const & f, float timeStep) {
	velocity += f * timeStep / mass;
}

void RigidObjectPhysicsComponent::moment(glm::vec3 const & M, float timeStep) {

	// solve for alpha
	auto alpha = invI * (M - glm::cross(omega, I * omega));
	// apply alpha
	omega += alpha * timeStep;
}

void RigidObjectPhysicsComponent::linStep(float timeStep) {
	position += velocity * timeStep;
}

void RigidObjectPhysicsComponent::rotStep(float timeStep) {

	auto length = glm::length(omega);
	if (length > 0) {
        auto dirOmega = omega / length;
        auto dOmega = length * timeStep;
        glm::mat3 metaRot;
        if (dOmega == 0) {
            metaRot = glm::mat3(1.0f);
        }
        else {
            metaRot = glm::mat3(glm::rotate(glm::mat4(1.0f), dOmega, dirOmega));
        }
        rotM = metaRot * rotM;
	}
}

void RigidObjectPhysicsComponent::step(float timeStep) {

	linStep(timeStep);
	rotStep(timeStep);
}
