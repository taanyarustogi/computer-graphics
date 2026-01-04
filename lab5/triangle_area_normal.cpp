#include "triangle_area_normal.h"
#include <Eigen/Geometry>

// used tutorial slides for hints

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
  Eigen::RowVector3d side1 = b - a;
  Eigen::RowVector3d side2 = c - a;
  Eigen::RowVector3d cross_product = side1.cross(side2);
  cross_product *= 0.5;

  return cross_product;
}
