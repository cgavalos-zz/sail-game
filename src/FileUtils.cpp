#include "FileUtils.h"

#include <fstream>
#include <string>
#include <functional>
#include <algorithm>

std::vector<std::string> getLines(std::string const & filename) {

	std::vector<std::string> lines;
	std::string line;

	std::ifstream inFile(filename);

	while (getline(inFile, line)) {

		lines.push_back(line);
	}

	inFile.close();

	return lines;
}

std::string combine(std::vector<std::string> const & lines) {

	std::string string;

	std::for_each(lines.begin(), lines.end(),
		[&string](std::string line) {

		string.append(line);
		string.append("\n");
	});

	return string;
}

std::pair<std::vector<glm::vec3>, std::vector<unsigned int>>
getVDataFromFile(std::string const & filename) {

	std::vector<glm::vec3> newVertices;
	std::vector<unsigned int> newElements;
	std::vector<std::string> lines = getLines(filename);
	bool broken = false;

	std::for_each(lines.begin(), lines.end(),
		[&broken, &newVertices, &newElements](std::string _line) {

		std::string line = _line;
		if (line == "") {
			broken = true;
		}
		else {
			if (!broken) {
				glm::vec3 temp(0.0f, 0.0f, 0.0f);
				for (int i = 0; i < 3; i++) {
					size_t spaceIndex = line.find(" ");
					temp[i] = std::stof(line.substr(0, spaceIndex));
					line = line.substr(spaceIndex + 1, line.length() - (spaceIndex + 1));
				}
				newVertices.push_back(temp);
			}
			else {
				for (int i = 0; i < 3; i++) {
					size_t spaceIndex = line.find(" ");
					newElements.push_back(std::stoi(line.substr(0, spaceIndex)));
					line = line.substr(spaceIndex + 1, line.length() - (spaceIndex + 1));
				}
			}
		}

	});

	return std::pair<std::vector<glm::vec3>, std::vector<unsigned int>>(newVertices, newElements);
}
