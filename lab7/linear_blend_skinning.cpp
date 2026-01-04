#include "linear_blend_skinning.h"
// used tutorial slides for steps and equation

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  const int n_vertices = V.rows();
  const int n_bones = skeleton.size();
  U.resize(n_vertices, 3);
  U.setZero();
  for (int i = 0; i < n_vertices; i++) {
	  Eigen::Vector3d v_h;
	  v_h = V.row(i).transpose();
	  for (int j = 0; j < n_bones; j++) {
		  if (skeleton[j].weight_index < 0) {
			  continue;
		  }
		  double w_ij = W(i, skeleton[j].weight_index);
		  U.row(i) +=  T[j] * v_h * w_ij;
	  }
  }
}
