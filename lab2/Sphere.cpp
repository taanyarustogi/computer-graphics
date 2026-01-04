#include "Sphere.h"
#include "Ray.h"

// used tutorial slides for equation

bool Sphere::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	double a = ray.direction.dot(ray.direction);
	double b = 2 * ray.direction.dot(ray.origin) - 2 * ray.direction.dot(center);
	double c = center.dot(center) + ray.origin.dot(ray.origin) - 2 * ray.origin.dot(center) - radius * radius;

	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return false;
	}
	else {
		double sqrt_discriminant = sqrt(discriminant);
		double t1 = (-b - sqrt_discriminant) / (2 * a);
		double t2 = (-b + sqrt_discriminant) / (2 * a);
		if (t1 >= min_t && t2 >= min_t) {
			t = std::min(t1, t2);
			n = (ray.origin + t * ray.direction - center).normalized();
			return true;
		}
		else if (t1 >= min_t) {
			t = t1;
			n = (ray.origin + t * ray.direction - center).normalized();
			return true;
		}
		else if (t2 >= min_t) {
			t = t2;
			n = (ray.origin + t * ray.direction - center).normalized();
			return true;
		}
		else {
			return false;
		}
	}
}

