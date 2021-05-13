#ifndef __NODE_H_
#define __NODE_H_
#include <memory>
namespace almtree{
    enum COLOR{ RED, BLACK };
}

struct Node{
    int key;
    std::shared_ptr<void> data;
    almtree::COLOR color;
    Node* left;
    Node* right;
    Node* parent;
    Node(int key);
    Node(const Node& cpy);
    Node* sibling();
    bool isOnLeft();
};


#endif // __NODE_H_
