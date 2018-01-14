#pragma once

#include <GL/glew.h>
#include <string>

#include <vector>

void handleIncludes(std::vector<std::string> & lines);
GLuint shaderSetup (GLenum type, std::string const & filename);
GLuint programSetup (
	std::vector<GLenum> const & types,
	std::vector<std::string> const & filenames);
