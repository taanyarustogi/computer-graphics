#include "transformed_tips.h"
#include "forward_kinematics.h"
// used the tutorial slides for steps

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> > T;
  forward_kinematics(skeleton, T);

  const int num_tips = b.size();
  Eigen::VectorXd xb(3*num_tips);
  for(int i = 0; i < num_tips; i++)
  {
	const Bone & bone = skeleton[b(i)];
	Eigen::Vector4d canonical_tip_pos(0, bone.length, 0, 1);
	Eigen::Vector4d rest_tip_pos = bone.rest_T * canonical_tip_pos;
	Eigen::Vector4d tip_pos = T[b(i)] * rest_tip_pos;
	xb.segment<3>(3*i) = tip_pos.head<3>();
  }
  return xb;
}
