#include "WaterSurface.h"

WaterSurface::WaterSurface(size_t gridUnitsPerSide, float gridWidth) :
	wspc(gridUnitsPerSide, gridWidth),
	wsgc(
		wspc.getNumGridUnitsPerSide(),
		wspc.getNumHeightsPerSide(),
		wspc.getNumElements(),
		wspc.getHeightVector(),
		wspc.getUnitSize()) {
}

WaterSurfacePhysicsComponent const & WaterSurface::getPhysicsComponent() const {
	return wspc;
}

WaterSurfaceGraphicsComponent const & WaterSurface::getGraphicsComponent() const {
	return wsgc;
}

void WaterSurface::update(Player const & player) {
	wspc.update(
		wsgc.getUpdateFunction(),
		player);
	wsgc.update(wspc.getModelMatrix());
}

// TODO Finish
PointForce WaterSurface::buoyantForce(Triangle const & t) const {
	// Get centroid of triangle.
    glm::vec3 centroid = t.getCentroid();
	// Get plane of surface above centroid.
    Plane plane = wspc.getPlane(centroid);
	// Clip triangle to get triangles above and below the surface.
	// For triangles above:
	//     Apply atmospheric pressure to centroid.
	// For triangles below:
	//     Apply water pressure to centroid.
	plane.getPoint();
	PointForce pf;
	return pf;
}
