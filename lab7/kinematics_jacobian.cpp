#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include "copy_skeleton_at.h"
#include <iostream>
// used tutorial slides for steps and equation

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
	J.resize(b.size() * 3, skeleton.size() * 3);
	J.setZero();
	Eigen::VectorXd tips = transformed_tips(skeleton, b);
	double delta = 1e-7;

	Eigen::VectorXd A(skeleton.size() * 3);
	for (int k = 0; k < skeleton.size(); k++) {
		A[k * 3 + 0] = skeleton[k].xzx[0];
		A[k * 3 + 1] = skeleton[k].xzx[1];
		A[k * 3 + 2] = skeleton[k].xzx[2];
	}

	for (int i = 0; i < skeleton.size(); i++) {
		for (int j = 0; j < 3; j++) {
			Eigen::VectorXd A_pert = A;
			A_pert[i * 3 + j] += delta;
			Skeleton perturbed_skeleton = copy_skeleton_at(skeleton, A_pert);
			Eigen::VectorXd tips_perturbed = transformed_tips(perturbed_skeleton, b);
			for (int idx = 0; idx < b.size(); idx++) {
				for (int coord = 0; coord < 3; coord++) {
					double derivative = (tips_perturbed[idx * 3 + coord] - tips[idx * 3 + coord]) / delta;
					J(idx * 3 + coord, i * 3 + j) = derivative;
				}
			}
		}
	}
}
