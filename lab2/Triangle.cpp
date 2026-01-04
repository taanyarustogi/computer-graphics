#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Dense>

// used tutorial slides for equations

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d v0 = std::get<0>(corners);
  Eigen::Vector3d v1 = std::get<1>(corners);
  Eigen::Vector3d v2 = std::get<2>(corners);
  Eigen::Vector3d t1 = v1 - v0;
  Eigen::Vector3d t2 = v2 - v0;

  Eigen::Matrix3d A;
  A.col(0) = t1;
  A.col(1) = t2;
  A.col(2) = -ray.direction;
 
  if (A.determinant() == 0) {
	  return false;
  }

  Eigen::Vector3d x = A.inverse() * (ray.origin - v0);

  double alpha = x(0);
  double beta = x(1);
  t = x(2);

  if (alpha < 0 || beta < 0 || alpha + beta > 1) {
	  return false;
  }

  if (t < min_t) {
	  return false;
  }
  n = t1.cross(t2).normalized();
  return true;
}


