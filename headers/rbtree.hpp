#ifndef __RBTREE_H_
#define __RBTREE_H_
#include "node.hpp"
#include <vector>

class RbTree{
    private:
        Node* root;
        Node* insert(Node* root, Node* newNode);
        void fixTreeAfterInsert(Node* &root, Node*& newNode);
        void rotateLeft(Node*& root, Node*& newNode);
        void rotateRight(Node*& root, Node*& newNode);
        Node* replacementSearch(Node* x);
        Node* successor(Node* x);
        void fixDoubleBlack(Node* x);
    public:
        RbTree();
        ~RbTree();
        Node* rbInsert(const int& key);
        void rbDelete(Node* node);
        std::vector<Node*> getLevelOrder();
        Node* getRoot();
        Node* search(const int& key);
        Node* popMin();
};

#endif // __RBTREE_H_
