#include "UBOManager.h"

#include <vector>
#include "ShaderMisc.h"
#include "glm/gtc/type_ptr.hpp"
#include "TypeSize.h"

UBOManager::UBOManager() {

	std::vector<GLenum> types({ GL_VERTEX_SHADER, GL_FRAGMENT_SHADER });
	std::vector<std::string> filenames({ "glsl/managerVert.glsl", "glsl/managerFrag.glsl" });

	program = programSetup(types, filenames);

	uboIndex = glGetUniformBlockIndex(
		program,
		blockName);

	glGetActiveUniformBlockiv(
		program,
		uboIndex,
		GL_UNIFORM_BLOCK_DATA_SIZE,
		&uboSize);

	buffer = new char[uboSize];

	glGetUniformIndices(program, numUniforms, names, indices);
	glGetActiveUniformsiv(
		program,
		numUniforms,
		indices,
		GL_UNIFORM_OFFSET,
		offset);

	glGetActiveUniformsiv(
		program,
		numUniforms,
		indices,
		GL_UNIFORM_SIZE,
		size);

	glGetActiveUniformsiv(
		program,
		numUniforms,
		indices,
		GL_UNIFORM_TYPE,
		type);

	glGenBuffers(1, &ubo);
}

UBOManager::~UBOManager() {
	delete[] buffer;
}

void UBOManager::update(
	Player const & player,
	SkyParameters const & skyParameters,
	WindowParameters const & windowParameters) const {

	glm::vec4 sunColor = glm::vec4(1, 1, 1, 1);
	glm::vec4 skyBlue = glm::vec4(4.0f / 255.0f, 94.0f / 255.0f, 172.0f / 255.0f, 255.0f);
	glm::mat4 view = player.getCamera().getTransform();
	glm::vec3 sunDirection = glm::mat3(view) *
		skyParameters.getSunDirection();
	float dotAngle = skyParameters.getDotAngle();
	glm::vec2 windowSize = windowParameters.getWindowSize();
	float fovy = windowParameters.getFOVY();
	float aspectRatio = windowParameters.getAspectRatio();
	glm::mat4 projection = windowParameters.getProjectionMatrix();

	void * pointers[] = {
		glm::value_ptr(sunColor),
		glm::value_ptr(skyBlue),
		glm::value_ptr(sunDirection),
		&dotAngle,
		glm::value_ptr(windowSize),
		&fovy,
		&aspectRatio,
		glm::value_ptr(view),
		glm::value_ptr(projection) };

	//memcpy((void *)((int)buffer + offset[0]), glm::value_ptr(sunColor), size[0] * TypeSize(type[0]));

	for (unsigned int i = 0; i < numUniforms; i++) {
		memcpy((char*)((long)buffer + (long)offset[i]), pointers[i], size[i] * TypeSize(type[i]));
	}

	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, uboSize, buffer, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex, ubo);
}
