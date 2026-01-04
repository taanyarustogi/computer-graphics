#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>
// used tutorial slides for steps and equations

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  f = [&](const Eigen::VectorXd & A)->double
  {
		  Eigen::VectorXd tips = transformed_tips(copy_skeleton_at(skeleton, A), b);
		  return (tips - xb0).squaredNorm();
  };
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
		  Skeleton cops = copy_skeleton_at(skeleton, A);
		  Eigen::VectorXd tips = transformed_tips(cops, b);
		  Eigen::MatrixXd J;
		  kinematics_jacobian(cops, b, J);
		  return 2 * J.transpose() * (tips - xb0);  
  };
  proj_z = [&](Eigen::VectorXd & A)
  {
    for (int i = 0; i < skeleton.size(); i++)
	{
	  for (int j = 0; j < 3; j++)
	  {
		  double minA = skeleton[i].xzx_min[j];
		  double maxA = skeleton[i].xzx_max[j];
		  A[i * 3 + j] = std::min(std::max(A[i * 3 + j], minA), maxA);
	  }
	}
  };
}
