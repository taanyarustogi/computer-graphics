#include "point_box_squared_distance.h"

// use notes from tutorial slides

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
	double sqrD = 0.0;
	for (int i = 0; i < 3; i++) {
		if (query[i] < box.min_corner[i]) {
			double d = box.min_corner[i] - query[i];
			sqrD += d * d;
		}
		else if (query[i] > box.max_corner[i]) {
			double d = query[i] - box.max_corner[i];
			sqrD += d * d;
		}
	}
	return sqrD;
}
