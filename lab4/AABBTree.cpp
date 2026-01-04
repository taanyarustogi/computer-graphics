#include "AABBTree.h"
#include "insert_box_into_box.h"

// use notes from tutorial slides

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
	box = BoundingBox();
	for (int i = 0; i < objects.size(); i++) {
		insert_box_into_box(objects[i]->box, box);
	}
	if (objects.size() == 1) {
		left = objects[0];
		right = nullptr;
	} else if (objects.size() == 2) {
		left = objects[0];
		right = objects[1];
	} else {
		int axis;
		double x = box.max_corner[0] - box.min_corner[0];
		double y = box.max_corner[1] - box.min_corner[1];
		double z = box.max_corner[2] - box.min_corner[2];
		if (x >= y && x >= z) {
			axis = 0;
		} else if (y >= z) {
			axis = 1;
		} else {
			axis = 2;
		}
		double mid = 0.5 * (box.max_corner[axis] + box.min_corner[axis]);
		std::vector<std::shared_ptr<Object> > left_objects;
		std::vector<std::shared_ptr<Object> > right_objects;
		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->box.center()[axis] < mid) {
				left_objects.push_back(objects[i]);
			} else {
				right_objects.push_back(objects[i]);
			}
		}
		if (left_objects.empty()) {
			left_objects.push_back(right_objects.back());
			right_objects.pop_back();
		}
		else if (right_objects.empty()) {
			right_objects.push_back(left_objects.back());
			left_objects.pop_back();
		}

		left = std::make_shared<AABBTree>(left_objects, depth + 1);
		right = std::make_shared<AABBTree>(right_objects, depth + 1);
	}
}
