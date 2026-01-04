#include "ray_intersect_triangle.h"
#include <Eigen/Dense>

// used code from assignment 3

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
	Eigen::Vector3d a = A.transpose();
	Eigen::Vector3d b = B.transpose();
	Eigen::Vector3d c = C.transpose();

	Eigen::Vector3d t1 = b - a;
	Eigen::Vector3d t2 = c - a;
	Eigen::Matrix3d A_mat;
	A_mat.col(0) = t1;
	A_mat.col(1) = t2;
	A_mat.col(2) = -ray.direction;

	if (A_mat.determinant() == 0) {
		return false;
	}

	Eigen::Vector3d x = A_mat.inverse() * (ray.origin - a);

	double alpha = x(0);
	double beta = x(1);
	t = x(2);

	if (alpha < 0 || beta < 0 || alpha + beta > 1) {
		return false;
	}

	if (t < min_t || t > max_t) {
		return false;
	}

	return true;

}

