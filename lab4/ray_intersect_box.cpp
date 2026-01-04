#include "ray_intersect_box.h"
#include <iostream>

// use notes from tutorial slides

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
	double t_enter = min_t;
	double t_exit = max_t;
	for (int i = 0; i < 3; i++) {
		double t_min = (box.min_corner[i] - ray.origin[i]) / ray.direction[i];
		double t_max = (box.max_corner[i] - ray.origin[i]) / ray.direction[i];

		if (t_min > t_max) {
			double temp = t_min;
			t_min = t_max;
			t_max = temp;
		}
		if (t_min > t_enter) {
			t_enter = t_min;
		}
		if (t_max < t_exit) {
			t_exit = t_max;
		}
		if (t_enter > t_exit) {
			return false;
		}
	}
	return true;
}
