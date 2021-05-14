#ifndef __RBTREE_H_
#define __RBTREE_H_
#include "node.hpp"
#include <memory>
#include <vector>

class RbTree{
    private:
        Node* root;
        Node* minNode;
        Node* insert(Node* root, Node* newNode);
        void fixTreeAfterInsert(Node* &root, Node* newNode);
        void rotateLeft(Node*& root, Node*& newNode);
        void rotateRight(Node*& root, Node*& newNode);
        Node* replacementSearch(Node* x);
        Node* successor(Node* x);
        void fixDoubleBlack(Node* x);
    public:
        RbTree();
        ~RbTree();

        /**
        * @brief Behelyez egy új kulcsot a piros-fekete fába.
        * Az rbInsert függvény először végrehajt egy standard bináris-keresőfa beszúrást,
        * utána pedig (ha szükséges) kijavítja az esetleges piros-fekete tulajdonság
        * megsértését a fixTreeAfterInsert privát metódussal.
        *
        * @param key A kulcs, ami alapjan el lesz rendezve a csomópont a keresőfában.
        *
        * @ret Az újonnan létrehozott csomopónt.
        * 
        */
        Node* rbInsert(const int& key);

        /**
         *
         * */
        void rbDelete(Node* node);
        std::vector<Node*> getLevelOrder();
        Node* getRoot();
        Node* search(const int& key);
        std::shared_ptr<void> popMin();
};

#endif // __RBTREE_H_
