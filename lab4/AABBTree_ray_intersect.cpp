#include "AABBTree.h"

// use notes from tutorial slides

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
	if (!ray_intersect_box(ray, box, min_t, max_t)) {
		return false;
	}
	double t_left = std::numeric_limits<double>::infinity();
	double t_right = std::numeric_limits<double>::infinity();
	std::shared_ptr<Object> left_child = nullptr;
	std::shared_ptr<Object> right_child = nullptr;

	bool hitl = false;
	if (left) {
		hitl = left->ray_intersect(ray, min_t, max_t, t_left, left_child);
		if (hitl && !left_child) {
			left_child = left;
		}
	}

	bool hitr = false;
	if (right) {
		hitr = right->ray_intersect(ray, min_t, max_t, t_right, right_child);
		if (hitr && !right_child) {
			right_child = right;
		}
	}

	if (hitl && hitr) {
		if (t_left < t_right) {
			t = t_left;
			descendant = left_child;
		}
		else {
			t = t_right;
			descendant = right_child;
		}
		return true;
	}
	else if (hitl) {
		t = t_left;
		descendant = left_child;
		return true;
	}
	else if (hitr) {
		t = t_right;
		descendant = right_child;
		return true;
	}
	return false;
}

