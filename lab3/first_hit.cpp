#include <iostream>
#include "first_hit.h"

// used tutorial slides for information

bool first_hit(
	const Ray& ray,
	const double min_t,
	const std::vector< std::shared_ptr<Object> >& objects,
	int& hit_id,
	double& t,
	Eigen::Vector3d& n)
{
	t = std::numeric_limits<double>::infinity();
	bool hit = false;
	for (int i = 0; i < objects.size(); i++) {
		double temp_t;
		Eigen::Vector3d temp_n;
		if (objects[i]->intersect(ray, min_t, temp_t, temp_n)) {
			hit = true;
			if (temp_t < t) {
				t = temp_t;
				hit_id = i;
				n = temp_n;
			}
		}
	}
	return hit;
}
