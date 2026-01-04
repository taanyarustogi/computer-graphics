#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

// use notes from tutorial slides

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
    sqrd = std::numeric_limits<double>::infinity();
    descendant = nullptr;

    if (root == nullptr) {
        return false;
    }

    std::priority_queue<
        std::pair<double, std::shared_ptr<Object>>,
        std::vector<std::pair<double, std::shared_ptr<Object>>>,
        std::greater<>
    > queue;

    double root_dist = point_box_squared_distance(query, root->box);
    if (root_dist <= max_sqrd && root_dist >= min_sqrd) {
        queue.push({ root_dist, root });
    }
    else {
        return false;
    }

    while (queue.size() > 0) {
        auto [dist, obj] = queue.top();
        queue.pop();

        if (dist > sqrd || dist > max_sqrd || dist < min_sqrd) {
            continue;
        }

        auto tree = std::dynamic_pointer_cast<AABBTree>(obj);
        if (tree) {
            if (tree->left) {
                double left_dist = point_box_squared_distance(query, tree->left->box);
                if (left_dist <= max_sqrd) {
                    queue.push({ left_dist, tree->left });
                }
            }
            if (tree->right) {
                double right_dist = point_box_squared_distance(query, tree->right->box);
                if (right_dist <= max_sqrd) {
                    queue.push({ right_dist, tree->right });
                }
            }
        }
        else {
            double d = point_box_squared_distance(query, obj->box);
            if (d < sqrd && d >= min_sqrd) {
                sqrd = d;
                descendant = obj;
            }
        }
    }
    if (descendant == nullptr) {
        return false;
	}
    return true;
}
