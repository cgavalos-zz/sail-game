#include "SkyboxObjectGraphicsComponent.h"

#include "ShaderMisc.h"
#include "FileUtils.h"
#include <vector>

SkyboxObjectGraphicsComponent::SkyboxObjectGraphicsComponent() {

	auto pair = getVDataFromFile("skybox.txt");
	auto vertices = pair.first;
	auto elements = pair.second;

	vegc = VertexElementGraphicsComponent(vertices, elements);

	std::vector<GLenum> types({
		GL_VERTEX_SHADER, GL_FRAGMENT_SHADER });

	std::vector<std::string> filenames({
		"skyboxVert.glsl", "skyboxFrag.glsl" });

	program = programSetup(types, filenames);
	glUseProgram(program);

	GLuint pLoc = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(pLoc);
	glVertexAttribPointer(pLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void SkyboxObjectGraphicsComponent::update() const {
	
	vegc.use(program);
	vegc.draw();
}