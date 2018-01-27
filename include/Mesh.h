#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "Triangle.h"
#include <string>

class Mesh
{
private:
    std::vector<Triangle> _triangles;
    glm::mat4 _model_matrix;
public:
    Mesh(std::vector<Triangle> const & triangles, glm::mat4 const & model_matrix);
    Mesh(std::vector<glm::vec3> const & vertices, glm::mat4 const & model_matrix);
    Mesh(std::vector<glm::vec3> const & vertices, std::vector<unsigned int> const & elements, glm::mat4 const & model_matrix);
    std::vector<Triangle> const & getTriangles() const;
    glm::mat4 getModelMatrix() const;
    static Mesh fromDataFile ( std::string const & filename );
};

#endif // MESH_H_INCLUDED
