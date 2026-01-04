#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

// use notes from tutorial slides

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
	I = -1;
	sqrD = std::numeric_limits<double>::infinity();

	for (int i = 0; i < points.rows(); i++) {
		Eigen::RowVector3d difference = points.row(i) - query;
		double distance = difference[0] * difference[0] + difference[1] * difference[1] + difference[2] * difference[2];
		if (distance < sqrD) {
			sqrD = distance;
			I = i;
		}
	}
}
