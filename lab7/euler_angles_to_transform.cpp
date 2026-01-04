#include "euler_angles_to_transform.h"
// used the tutorial slides for steps

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
	double x1 = xzx(0) * 3.14159265358979323846 /180;
	double z = xzx(1) * 3.14159265358979323846 /180;
	double x2 = xzx(2) * 3.14159265358979323846 /180;

	Eigen::AngleAxisd R_x1(x1, Eigen::Vector3d::UnitX());
	Eigen::AngleAxisd R_z(z, Eigen::Vector3d::UnitZ());
	Eigen::AngleAxisd R_x2(x2, Eigen::Vector3d::UnitX());

	Eigen::Matrix3d R = (R_x1 * R_z * R_x2).toRotationMatrix();

	Eigen::Affine3d A = Eigen::Affine3d::Identity();
	A.linear() = R;
    return A;
}
