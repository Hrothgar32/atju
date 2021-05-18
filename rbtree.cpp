#include "rbtree.hpp"
#include "node.hpp"
#include <memory>
#include <type_traits>
#include <utility>
#include <queue>
#include <iostream>

using almtree::COLOR;

using namespace almtree;

RbTree::RbTree(){
    root = nullptr;
}

RbTree::~RbTree(){
    while(root != nullptr)
        this->rbDelete(root);
}

void RbTree::rotateLeft(Node*& root, Node*& nodePtr){
    Node* right = nodePtr->right;
    nodePtr->right = right->left;
    if(nodePtr->right != nullptr)
        nodePtr->right->parent = nodePtr;
    right->parent = nodePtr->parent;
    if(nodePtr->parent == nullptr)
        root = right;
    else if(nodePtr == nodePtr->parent->left)
        nodePtr->parent->left = right;
    else
        nodePtr->parent->right = right;
    right->left = nodePtr;
    nodePtr->parent = right;
}

void RbTree::rotateRight(Node*& root, Node*& nodePtr){
    Node* left = nodePtr->left;
    nodePtr->left = left->right;
    if(nodePtr->left != nullptr)
        nodePtr->left->parent = nodePtr;
    left->parent = nodePtr->parent;
    if(nodePtr->parent == nullptr)
        root = left;
    else if(nodePtr == nodePtr->parent->left)
        nodePtr->parent->left = left;
    else
        nodePtr->parent->right = left;
    left->right = nodePtr;
    nodePtr->parent = left;

}

Node* RbTree::insert(Node *root, Node* newNode){
    if(root == nullptr)
        return newNode;
    if(newNode->key <= root->key){
        root->left = insert(root->left, newNode);
        root->left->parent = root;
    }
    else if(newNode->key >= root->key){
        root->right = insert(root->right, newNode);
        root->right->parent = root;
    }
    return root;
}

void RbTree::fixTreeAfterInsert(Node*& root, Node* newNode){
    Node* parent = nullptr;
    Node* grand_parent = nullptr;
    while((newNode != root) && (newNode->color != BLACK) &&
          (newNode->parent->color == RED)){
              parent = newNode->parent;
              // A. eset: a szülő a nagyszülőnek bal gyermeke.
              grand_parent = newNode->parent->parent;
              if(parent == grand_parent->left){
                  Node* uncle = grand_parent->right;
                  if(uncle != nullptr && uncle->color == RED){
                      grand_parent->color = RED;
                      parent->color = BLACK;
                      uncle->color = BLACK;
                      newNode = grand_parent;
                  }
                  else{
                    //Bal-jobb eset: Átalakítjuk egy balforgatással egy bal-bal esetre.
                     if(newNode == parent->right){
                        rotateLeft(root, parent);
                        newNode = parent;
                        parent = newNode->parent;
                     }
                     // Bal-bal eset
                     rotateRight(root, grand_parent);
                     std::swap(parent->color, grand_parent->color);
                     newNode = parent;
                  }
              }
              else{
                  //B. eset: a szülő a nagyszülőnek jobb gyermeke.
                  Node* uncle = grand_parent->left;
                  //Ha a nagybácsi piros, akkor egy átszínezéssel megvagyunk.
                  if(uncle != nullptr && uncle->color == RED){
                      grand_parent->color = RED;
                      parent->color = BLACK;
                      uncle->color = BLACK;
                      newNode = grand_parent;
                  }
                  else{
                    //Jobb-bal eset: Átalakítjuk egy jobbforgatással egy jobb-jobb esetre.
                     if(newNode == parent->left){
                        rotateRight(root, parent);
                        newNode = parent;
                        parent = newNode->parent;
                     }
                     //Jobb-jobb eset
                     rotateLeft(root, grand_parent);
                     std::swap(parent->color, grand_parent->color);
                     newNode = parent;
                  }
              }
    }
    root->color = BLACK;
}

Node* RbTree::rbInsert(const int& key){
    Node* newNode = new Node(key);
    root = insert(root, newNode);
    fixTreeAfterInsert(root, newNode);
    if(minNode == nullptr)
        minNode = newNode;
    else if(newNode->key < minNode->key)
        minNode = newNode;
    return newNode;
}

Node* RbTree::search(const int& key){
    Node* tmp = root;
    while(tmp->key != key && tmp != nullptr){
        if(tmp->key > key){
            tmp = tmp->left;
        }
        else{
            tmp = tmp->right;
        }
    }
    return tmp;
}

Node* RbTree::successor(Node* x){
    Node* temp = x;
    while(temp->left != nullptr)
        temp = temp->left;
    return temp;
}

Node* RbTree::replacementSearch(Node* x){
    if(x->left != nullptr && x->right != nullptr)
        return successor(x->right);

    if(x->left == nullptr && x->right == nullptr)
        return nullptr;
    if(x->left != nullptr)
        return x->left;
    else
        return x->right;
}

void RbTree::rbDelete(Node* node){
    Node* u = replacementSearch(node);
    bool bothBlack = (( u == nullptr || u->color == BLACK ) && node->color == BLACK);
    Node* parent = node->parent;

    // A leváltó csúcs nullptr.tehát node egy levél.
    if(u == nullptr){
        if(node == root){
          root = nullptr;
        }
        else{
            //A levél fekete ezért a nullptr, ami leváltja, duplafekete lesz.
            if(bothBlack)
                fixDoubleBlack(node);
            else{
                Node* sibling = node->sibling();
                //Mivel a node csúcs levél, ezért ahhoz, hogy uniform maradjon a fekete
                //magasság, a testvére (ha nem nullptr) feltétlen piros kell legyen.
                if(sibling != nullptr)
                    sibling->color = RED;
            }
            if(node->isOnLeft())
                parent->left = nullptr;
            else
                parent->right = nullptr;
        }
        delete node;
    }
    else{
        // Nodenak egy gyereke van.
        if(node->left == nullptr || node->right == nullptr){
            if(node == root){
                node->key = u->key;
                node->data = u->data;
                node->left = node->right = nullptr;
                delete u;
            }
            else{
                if(node->isOnLeft()){
                    parent->left = u;
                }
                else{
                    parent->right = u;
                }
                delete node;
                u->parent = parent;
                // A leváltó is fekete, fel kell oldjuk a dupla-feketét.
                if(bothBlack){
                    fixDoubleBlack(u);
                }
                // Egyszerű eset, a leváltó csúcs piros, ezért átszínezzük
                else{
                    u->color = BLACK;
                }
            }
        }
        // A nodenak két gyereke van, ezért kicseréljük a leváltó adatait a node adataival,
        // és meghívjuk a törlést a leváltóra.
        else{
            std::swap(u->key, node->key);
            std::swap(u->data, node->data);
            rbDelete(u);
        }
    }
}

void RbTree::fixDoubleBlack(Node* x){
    if(x != root){
        Node* sibling = x->sibling();
        Node* parent = x->parent;
        if(sibling == nullptr){
            fixDoubleBlack(parent);
        }
        else{
            if(sibling->color == RED){
                parent->color = RED;
                sibling->color = BLACK;
                if(sibling->isOnLeft()){
                    rotateRight(root, parent);
                }
                else{
                    rotateLeft(root, parent);
                }
                fixDoubleBlack(x);
            }
            else{
                if((sibling->left != nullptr && sibling->left->color == RED) ||
                (sibling->right != nullptr && sibling->right->color == RED)){
                    if(sibling->left != nullptr && sibling->left->color == RED){
                        if(sibling->isOnLeft()){
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rotateRight(root, parent);
                        }
                        else{
                            sibling->left->color = parent->color;
                            rotateRight(root, sibling);
                            rotateLeft(root, parent);
                        }
                    }
                    else{
                        if(sibling->isOnLeft()){
                            sibling->right->color = parent->color;
                            rotateLeft(root, sibling);
                            rotateRight(root, parent);
                        }
                        else{
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            rotateLeft(root, parent);
                        }
                    }
                    parent->color = BLACK;
                }
                else{
                    sibling->color = RED;
                    if(parent->color == BLACK){
                        fixDoubleBlack(parent);
                    }
                    else{
                        parent->color = BLACK;
                    }
                }
            }
        }
    }
}

std::vector<Node*> RbTree::getLevelOrder(){
    std::vector<Node*> levelOrderedList;
    if(root == nullptr){
        return levelOrderedList;
    }
    std::queue<Node*> q;
    Node* curr;
    q.push(root);
    while(!q.empty()){
        curr = q.front();
        levelOrderedList.push_back(curr);
        q.pop();
        if(curr->left != nullptr)
            q.push(curr->left);
        if(curr->right != nullptr)
            q.push(curr->right);
    }
    return levelOrderedList;
}

Node* RbTree::getRoot(){
    return root;
}

std::shared_ptr<void> RbTree::popMin(){
    if(minNode == nullptr)
        return nullptr;
    Node* parent = minNode->parent;
    std::shared_ptr<void> data = minNode->data;
    rbDelete(minNode);
    minNode = parent;
    return data;
}
