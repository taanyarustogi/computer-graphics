#include "projected_gradient_descent.h"
#include "line_search.h"
// used tutorial slides for steps and equation

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
	for (int iter = 0; iter < max_iters; iter++) {
		Eigen::VectorXd grad = grad_f(z);
		if (grad.isZero())
		{
			return;
		}
		Eigen::VectorXd d = -grad;
		double step_size = line_search(f, proj_z, z, d, 10000);
		Eigen::VectorXd z_new = z + step_size * d;
		proj_z(z_new);
		z = z_new;
	}
}
