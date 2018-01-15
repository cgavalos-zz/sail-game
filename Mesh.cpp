#include "Mesh.h"

Mesh::Mesh (std::vector<Triangle> triangles) :
    _triangles (triangles) {}

Mesh::Mesh (std::vector<glm::vec3> vertices) :
    _triangles (vertices.size() / 3)
{
    for (unsigned int i = 0; i < vertices.size(); i += 3)
    {
        _triangles.at (i / 3) =
            Triangle (
                vertices.at (i + 0),
                vertices.at (i + 1),
                vertices.at (i + 2));
    }
}

Mesh::Mesh (std::vector<glm::vec3> vertices, std::vector<unsigned int> elements) :
    _triangles(elements.size() / 3)
{
    for (unsigned int i = 0; i < elements.size(); i += 3)
    {
        _triangles.at (i / 3) =
            Triangle (
                vertices.at (elements.at(i + 0)),
                vertices.at (elements.at(i + 1)),
                vertices.at (elements.at(i + 2)));
    }
}

std::vector<Triangle> const &
Mesh::getTriangles() const {
    return _triangles;
}
