#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>
// used the tutorial slides for steps and equations

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
	if (keyframes.size() == 0) {
		return Eigen::Vector3d::Zero();
	}

	if (keyframes.size() == 1) {
		return keyframes.front().second;
	}

	double duration = keyframes.back().first - keyframes.front().first;
	double t_frame = std::fmod(t - keyframes.front().first, duration);
	if (t_frame < 0) {
		t_frame += duration;
	}
	t_frame += keyframes.front().first; 


  for (int i = 0; i < static_cast<int>(keyframes.size()) - 1; i++) {
	  if (t_frame >= keyframes[i].first && t_frame <= keyframes[i + 1].first) {
		Eigen::Vector3d P0;
		double t0;
		Eigen::Vector3d P3;
		double t3;
		if (i == 0) {
			P0 = keyframes[i].second;
			t0 = keyframes[i].first;
		}
		else {
			P0 = keyframes[i - 1].second;
			t0 = keyframes[i - 1].first;
		}
	  Eigen::Vector3d P1 = keyframes[i].second;
	  double t1 = keyframes[i].first;
	  Eigen::Vector3d P2 = keyframes[i + 1].second;
	  double t2 = keyframes[i + 1].first;
	  if (i == static_cast<int>(keyframes.size()) - 2) {
		  P3 = keyframes[i + 1].second;
		  t3 = keyframes[i + 1].first;
	  }
	  else {
		  P3 = keyframes[i + 2].second;
		  t3 = keyframes[i + 2].first;
	  }

	  Eigen::Vector3d m0 = (P2 - P0)/(t2-t0);
	  Eigen::Vector3d m1 = (P3 - P1)/(t3-t1);



	  double dt = t2 - t1;
	  double s = (t_frame - t1) / dt;

	  Eigen::Vector3d result = (2 * P1 - 2 * P2 + m0 + m1) * (s * s * s) -
							   (3 * P1 - 3 * P2 + 2 * m0 + m1) * (s * s) +
							   m0 * s + 
							   P1;
	  return result;
	}
  }
  return Eigen::Vector3d(0, 0, 0);
}
