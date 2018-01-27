#include "WaterSurface.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

WaterSurface::WaterSurface (size_t gridUnitsPerSide, float gridWidth) :
    wspc (gridUnitsPerSide, gridWidth),
    wsgc (
        wspc.getNumGridUnitsPerSide(),
        wspc.getNumHeightsPerSide(),
        wspc.getNumElements(),
        wspc.getHeightVector(),
        wspc.getUnitSize())
{
}

WaterSurfacePhysicsComponent const & WaterSurface::getPhysicsComponent() const
{
    return wspc;
}

WaterSurfaceGraphicsComponent const & WaterSurface::getGraphicsComponent() const
{
    return wsgc;
}

void WaterSurface::update (Player const & player)
{
    wspc.update (
        wsgc.getUpdateFunction(),
        player);
    wsgc.update (wspc.getModelMatrix());
}

// TODO Finish
PointForce
WaterSurface::buoyantForceOnTriangle (
    Triangle const & t,
    glm::vec3 const & up,
    float atmosphericPressure) const
{
    // Get centroid of triangle.
    glm::vec3 centroid = t.getCentroid();
    // Get plane of surface above centroid.
    Plane plane = wspc.getPlane (centroid);
    // Clip triangle to get triangles above and below the surface.
    std::pair<std::vector<Triangle>, std::vector<Triangle>>
            res = t.clip (plane, up);
    // For triangles above:
    //     Apply atmospheric pressure to centroid.
    std::vector<Triangle> above = res.first;
    std::vector<PointForce> aboveForces;

    for (Triangle t : above)
    {
        aboveForces.push_back (PointForce (t.getCentroid(), -t.getNormal(), t.getArea() * atmosphericPressure));
    }

    // For triangles below:
    //     Apply water pressure to centroid.
    std::vector<Triangle> below = res.second;
    std::vector<PointForce> belowForces;
    auto pressureFunc = wspc.getPressureLambda();

    for (Triangle t : below)
    {
        belowForces.push_back (PointForce (t.getCentroid(), -t.getNormal(), t.getArea() * (pressureFunc (t.getCentroid()) + atmosphericPressure)));
    }

    // Return weighted sum of all forces.
    return PointForce::codirectionalWeightedSum (
               std::vector<PointForce> (
    {
        PointForce::codirectionalWeightedSum (aboveForces),
        PointForce::codirectionalWeightedSum (belowForces)
    }));
}

std::vector<PointForce>
WaterSurface::buoyantForcesOnMesh (
    Mesh const & m,
    glm::vec3 const & up,
    float atmosphericPressure) const
{
    std::vector<PointForce> triangleForces;
    glm::mat4 modelMatrix = m.getModelMatrix();

    for (Triangle t : m.getTriangles())
    {
        triangleForces.push_back (buoyantForceOnTriangle (t.transform (modelMatrix), up, atmosphericPressure));
    }

    return triangleForces;
}
