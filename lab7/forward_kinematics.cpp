#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function
// used the tutorial slides for steps

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  for (int i = 0; i < static_cast<int>(skeleton.size()); i++) {
	const Bone & bone = skeleton[i];
	Eigen::Affine3d local_T = bone.rest_T * euler_angles_to_transform(bone.xzx) * bone.rest_T.inverse();
	if (bone.parent_index == -1) {
	  T[i] = local_T;
	} else {
	  T[i] = T[bone.parent_index] * local_T;
	}
  }
}
