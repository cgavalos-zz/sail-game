#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <utility>
#include <string>

std::vector<std::string> getLines(std::string const & filename);
std::string combine(std::vector<std::string> const & lines);
std::pair<std::vector<glm::vec3>, std::vector<unsigned int>>
getVDataFromFile(std::string const & filename);
