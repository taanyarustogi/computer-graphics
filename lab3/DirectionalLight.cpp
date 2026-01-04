// used tutorial slides for equations

#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & direction, double & max_t) const
{
  direction = (-d).normalized();
  max_t = std::numeric_limits<double>::infinity();
}

