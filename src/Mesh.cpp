#include "Mesh.h"
#include "FileUtils.h"

Mesh::Mesh (
    std::vector<Triangle> const & triangles,
    glm::mat4 const & model_matrix) :
    _triangles (triangles),
    _model_matrix(model_matrix) {}

Mesh::Mesh (
    std::vector<glm::vec3> const & vertices,
    glm::mat4 const & model_matrix) :
    _triangles (vertices.size() / 3),
    _model_matrix(model_matrix)
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

Mesh::Mesh (
    std::vector<glm::vec3> const & vertices,
    std::vector<unsigned int> const & elements,
    glm::mat4 const & model_matrix) :
    _triangles (elements.size() / 3),
    _model_matrix(model_matrix)
{
    for (unsigned int i = 0; i < elements.size(); i += 3)
    {
        _triangles.at (i / 3) =
            Triangle (
                vertices.at (elements.at (i + 0)),
                vertices.at (elements.at (i + 1)),
                vertices.at (elements.at (i + 2)));
    }
}

std::vector<Triangle> const &
Mesh::getTriangles() const
{
    return _triangles;
}

glm::mat4 Mesh::getModelMatrix() const
{
    return _model_matrix;
}

Mesh Mesh::fromDataFile ( std::string const & filename )
{
    std::pair<std::vector<glm::vec3>, std::vector<unsigned int>> pair = getVDataFromFile ( filename );
    return Mesh ( pair.first, pair.second, glm::mat4(1.0f) );
}
