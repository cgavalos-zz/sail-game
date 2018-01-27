#include "ShaderMisc.h"

#include "FileUtils.h"
#include <iostream>
#include <string>

void handleIncludes(std::vector<std::string> & lines) {

	for (unsigned int i = 0; i < lines.size(); i++) {

		std::string line = lines.at(i);
		std::string findString = "#include ";
		auto index = line.find(findString);

		if (index != std::string::npos) {

			std::string filename = line.substr(
				findString.size(),
				line.size() - findString.size());
			auto includeLines = getLines(filename);

			auto current = lines.begin();
			std::advance(current, i);
			lines.erase(current);

			current = lines.begin();
			std::advance(current, i);
			lines.insert(current, includeLines.begin(), includeLines.end());
		}
	}
}

GLuint shaderSetup (GLenum type, std::string const & filename) {

	auto lines = getLines(filename);

	handleIncludes(lines);

	auto code = combine(lines);

	std::vector<GLchar> ptr(code.c_str(), code.c_str() + code.size() + 1);
	const GLchar *chars = ptr.data();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &chars, NULL);
	glCompileShader(shader);

	GLsizei bufSize = 256;
	char *infoLog = new char[bufSize];
	GLsizei length;

	glGetShaderInfoLog(shader, bufSize, &length, infoLog);

	if (length != 0) {
		std::cout << filename << std::endl;
		std::cout << "SHADER LOG: " << infoLog << std::endl;
	}

	free(infoLog);

	return shader;
}

GLuint programSetup (
	std::vector<GLenum> const & types,
	std::vector<std::string> const & filenames) {

	GLuint program = glCreateProgram();

	unsigned int size = types.size();
	std::vector<GLuint> shaders(size);

	for (unsigned int i = 0; i < size; i++) {

		shaders[i] = shaderSetup(types[i], filenames[i]);
		glAttachShader(program, shaders[i]);
	}

	glLinkProgram(program);

	for (int i = size - 1; i >= 0; i--) {

		glDetachShader(program, shaders[i]);
	}

	GLsizei bufSize = 256;
	char *infoLog = new char[bufSize];
	GLsizei length;

	glGetProgramInfoLog(program, bufSize, &length, infoLog);

	if (length != 0) {
		std::cout << "PROGRAM LOG: " << infoLog << std::endl;
	}

	free(infoLog);

	return program;
}
