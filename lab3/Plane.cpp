#include "Plane.h"
#include "Ray.h"

// used tutorial slides for equation

bool Plane::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	if (ray.direction.dot(normal) == 0) {
		return false;
	}
	t = (point - ray.origin).dot(normal) / ray.direction.dot(normal);
	if (t < min_t) {
		return false;
	}
	n = normal;
	return true;
}

