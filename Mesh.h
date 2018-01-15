#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "Triangle.h"

class Mesh
{
private:
    std::vector<Triangle> _triangles;
public:
    Mesh(std::vector<Triangle> triangles);
    Mesh(std::vector<glm::vec3> vertices);
    Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> elements);
    std::vector<Triangle> const & getTriangles() const;
};

#endif // MESH_H_INCLUDED
