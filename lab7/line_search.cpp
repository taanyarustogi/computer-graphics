#include "line_search.h"
#include <iostream>
// used tutorial slides for steps and equation

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
	double f0 = f(z);
	double alpha = max_step;
	Eigen::VectorXd zj;
	while (alpha > 1e-7) {
		zj = z + alpha * dz;
		proj_z(zj);
		double fzj = f(zj);
		if (fzj < f0) {
			return alpha;
		}
		alpha *= 0.5;
	}
	return 0;
}
