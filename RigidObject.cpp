#include "RigidObject.h"

#include "FileUtils.h"

RigidObject::RigidObject (
    std::vector<glm::vec3> const & vertices,
    std::vector<unsigned int> const & elements ) :
    ropc ( vertices, elements, 1.0f ),
    rogc ( vertices, elements )
{
}

RigidObjectGraphicsComponent const & RigidObject::getGraphicsComponent() const
{
    return rogc;
}

void RigidObject::update ( WaterSurface const & waterSurface, float timeStep )
{
    ropc.update ( waterSurface, timeStep );
    rogc.update ( ropc.getModelMatrix() );
}

RigidObject RigidObject::fromDataFile ( std::string const & filename )
{
    std::pair<std::vector<glm::vec3>, std::vector<unsigned int>> pair = getVDataFromFile ( filename );
    return RigidObject ( pair.first, pair.second );
}
