#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 
#include <iostream>

// use notes from tutorial slides

void find_all_intersecting_pairs_using_AABBTrees(
    const std::shared_ptr<AABBTree>& rootA,
    const std::shared_ptr<AABBTree>& rootB,
    std::vector<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > >&
    leaf_pairs)
{
    if (rootA == nullptr || rootB == nullptr) {
        return;
    }

    std::list<
        std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>
    > queue;

    if (box_box_intersect(rootA->box, rootB->box)) {
        queue.push_back({ rootA, rootB });
    }
    else {
        return;
    }

    while (queue.size() > 0) {
        auto [nodeA, nodeB] = queue.front();
        queue.pop_front();

        auto treeA = std::dynamic_pointer_cast<AABBTree>(nodeA);
        auto treeB = std::dynamic_pointer_cast<AABBTree>(nodeB);

        if (treeA == nullptr && treeB == nullptr) {
			leaf_pairs.push_back({ nodeA, nodeB });
            continue;
        }
        else {
            if (treeA != nullptr && treeB != nullptr) {
                if (treeA->left && treeB->left && box_box_intersect(treeA->left->box, treeB->left->box)) {
                    queue.push_back({ treeA->left, treeB->left });
                }
                if (treeA->left && treeB->right && box_box_intersect(treeA->left->box, treeB->right->box)) {
                    queue.push_back({ treeA->left, treeB->right });
                }
                if (treeA->right && treeB->left && box_box_intersect(treeA->right->box, treeB->left->box)) {
                    queue.push_back({ treeA->right, treeB->left });
                }
                if (treeA->right && treeB->right && box_box_intersect(treeA->right->box, treeB->right->box)) {
                    queue.push_back({ treeA->right, treeB->right });
                }
            }
            else if (treeA != nullptr) {
                if (treeA->left && box_box_intersect(treeA->left->box, nodeB->box)) {
                    queue.push_back({ treeA->left, nodeB });
                }
                if (treeA->right && box_box_intersect(treeA->right->box, nodeB->box)) {
                    queue.push_back({ treeA->right, nodeB });
                }
            }
            else {
                if (treeB->left && box_box_intersect(nodeA->box, treeB->left->box)) {
                    queue.push_back({ nodeA, treeB->left });
                }
                if (treeB->right && box_box_intersect(nodeA->box, treeB->right->box)) {
                    queue.push_back({ nodeA, treeB->right });
                }
			}
        }
    }
}
