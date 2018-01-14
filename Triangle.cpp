#include "Triangle.h"

#include <iostream>

Triangle::Triangle(
	glm::vec3 const & _v1,
	glm::vec3 const & _v2,
	glm::vec3 const & _v3) {

	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	center = (v1 + v2 + v3) * (1.0f / 3);
	glm::vec3 crossProduct = glm::cross(v2 - v1, v3 - v1);
	float length = glm::length(crossProduct);
	area = length / 2;
	normal = crossProduct / length;
}

Triangle::Triangle() {}

Triangle::Triangle(
	glm::vec3 const & _v1,
	glm::vec3 const & _v2,
	glm::vec3 const & _v3,
	glm::vec3 const & _normal) {

	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	normal = _normal;
	center = (v1 + v2 + v3) * (1.0f / 3);
	glm::vec3 crossProduct = glm::cross(v2 - v1, v3 - v1);
	float length = glm::length(crossProduct);
	area = length / 2;
}

Triangle::Triangle(
	glm::vec3 const & _v1,
	glm::vec3 const & _v2,
	glm::vec3 const & _v3,
	glm::vec3 const & _normal,
	float _area) {

	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	normal = _normal;
	center = (v1 + v2 + v3) * (1.0f / 3);
	area = _area;
}

glm::vec3
Triangle::getCentroid() const {
    return center;
}

std::vector<Triangle> Triangle::tessellate() const {

	glm::vec3 v12 = (v1 + v2) * 0.5f;
	glm::vec3 v13 = (v1 + v3) * 0.5f;
	glm::vec3 v23 = (v2 + v3) * 0.5f;
	std::vector<Triangle> triangles(4);
	triangles[0] = Triangle(v1, v12, v13, normal, area / 4);
	triangles[1] = Triangle(v12, v2, v23, normal, area / 4);
	triangles[2] = Triangle(v12, v23, v13, normal, area / 4);
	triangles[3] = Triangle(v13, v23, v3, normal, area / 4);
	return triangles;
}

Triangle::PlaneStatus Triangle::plane_status(
	Plane const & plane,
	glm::vec3 const & up) const {

    auto a1 = plane.pointAbove(v1, up);
    auto a2 = plane.pointAbove(v2, up);
    auto a3 = plane.pointAbove(v3, up);

	if (a1 && a2 && a3) {
		return ABOVE;
	} else if (!a1 && !a2 && !a3) {
		return BELOW;
	} else {
		return CROSS;
	}
}

Triangle::PlaneStatus Triangle::partial_plane_status(
    Plane const & plane,
	glm::vec3 const & up) const {
	auto a1 = plane.pointAbove(v1, up);
	auto a2 = plane.pointAbove(v2, up);
	auto a3 = plane.pointAbove(v3, up);

	if (a1 || a2 || a3) {
		return ABOVE;
	} else {
		return BELOW;
	}
}

std::pair<std::vector<Triangle>, std::vector<Triangle>> Triangle::clip(
	Plane const & plane,
	glm::vec3 const & up) const {

	auto point_on_segment = [](glm::vec3 l1, glm::vec3 l2, glm::vec3 p) {
		return glm::dot(p - l1, p - l2) <= 0;
	};

	switch (plane_status(plane, up)) {
	case ABOVE:
		return std::make_pair(
			std::vector<Triangle>({ *this }),
			std::vector<Triangle>({}));
	case BELOW:
		return std::make_pair(
			std::vector<Triangle>({}),
			std::vector<Triangle>({ *this }));
	default:
		auto r12 = plane.lineIntersect(Line(v1, v2 - v1));
		auto v12 =
            r12.second == Plane::LineIntersect::NO_INTERSECT ||
            !point_on_segment(v1, v2, r12.first) ? v1 : r12.first;
		auto r23 = plane.lineIntersect(Line(v2, v3 - v2));
		auto v23 =
            r23.second == Plane::LineIntersect::NO_INTERSECT ||
            !point_on_segment(v2, v3, r23.first) ? v2 : r23.first;
		auto r31 = plane.lineIntersect(Line(v3, v1 - v3));
		auto v31 =
            r31.second == Plane::LineIntersect::NO_INTERSECT ||
            !point_on_segment(v3, v1, r31.first) ? v3 : r31.first;

		Triangle ta = Triangle(v1, v12, v31);
		Triangle tb = Triangle(v12, v2, v23);
		Triangle tc = Triangle(v23, v3, v31);
		Triangle td = Triangle(v12, v23, v31);

		std::vector<Triangle> tris;

		if (ta.area > 0) {
			tris.push_back(ta);
		}
		if (tb.area > 0) {
			tris.push_back(tb);
		}
		if (tc.area > 0) {
			tris.push_back(tc);
		}
		if (td.area > 0) {
			tris.push_back(td);
		}

		std::vector<Triangle> above;
		std::vector<Triangle> below;

		for (Triangle t : tris) {
			auto status = t.partial_plane_status(plane, up);
			if (status == BELOW) {
				below.push_back(t);
			} else {
				above.push_back(t);
			}
		}

		return std::make_pair(above, below);
	}
}
