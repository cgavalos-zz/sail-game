#pragma once

#include "GL/glew.h"

#include "WindowParameters.h"
#include "SkyParameters.h"
#include "Player.h"

class UBOManager {
private:
	const static GLuint numUniforms = 9;
	const char * blockName = "bigBlock";
	const char * names[numUniforms] = {
		"sunColor",
		"skyBlue",
		"sunDirection",
		"dotAngle",
		"windowSize",
		"fovy",
		"aspectRatio",
		"view",
		"projection"
	};

	GLuint program;
	GLuint uboIndex;
	GLchar * buffer;
	GLint uboSize;
	GLuint ubo;

	GLuint indices[numUniforms];
	GLint size[numUniforms];
	GLint offset[numUniforms];
	GLint type[numUniforms];
public:
	UBOManager();
	~UBOManager();
	void update(
		Player const & player,
		SkyParameters const & skyParameters,
		WindowParameters const & windowParameters) const;
};
