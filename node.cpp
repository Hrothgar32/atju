#include "node.hpp"

using namespace almtree;

Node::Node(int key){
    this->key = key;
    this->color = RED;
    left = right = parent = nullptr;
}

Node::Node(const Node& cpy){
    this->color = cpy.color;
    this->left = cpy.left;
    this->right = cpy.right;
    this->parent = cpy.parent;
    this->key = cpy.key;
}

bool Node::isOnLeft(){
    return this->parent->left == this;
}

Node* Node::sibling(){
    if(parent == nullptr)
        return nullptr;
    if(isOnLeft())
        return parent->right;
    else
        return parent->left;
}
