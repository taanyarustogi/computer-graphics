#include "insert_triangle_into_box.h"

// use notes from tutorial slides

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
	for (int i = 0; i < 3; i++) {
		if (a[i] < B.min_corner[i]) {
			B.min_corner[i] = a[i];
		}
		if (b[i] < B.min_corner[i]) {
			B.min_corner[i] = b[i];
		}
		if (c[i] < B.min_corner[i]) {
			B.min_corner[i] = c[i];
		}
		if (a[i] > B.max_corner[i]) {
			B.max_corner[i] = a[i];
		}
		if (b[i] > B.max_corner[i]) {
			B.max_corner[i] = b[i];
		}
		if (c[i] > B.max_corner[i]) {
			B.max_corner[i] = c[i];
		}
	}
}


