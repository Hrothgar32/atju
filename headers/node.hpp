#ifndef __NODE_H_
#define __NODE_H_
#include <memory>

/// A piros-fekete fa színeit tartalmazó névtér.
namespace almtree{
    enum COLOR{ RED, BLACK };
}

/// A csomópont a piros fekete fában.
struct Node{
    int key;
    //Általános adat.
    std::shared_ptr<void> data;
    almtree::COLOR color;
    Node* left;
    Node* right;
    Node* parent;
    Node(int key);
    Node(const Node& cpy);
    /**
     * @brief Visszatéríti a csomópont testvérét.
     * @returns A csomópont testvére.
     **/
    Node* sibling();

    /**
     * @brief Ellenőrzi, hogy a csomópont a szülője bal oldalán van-e.
     * @returns true ha a bal oldalon van, másképpp false
     **/
    bool isOnLeft();
};


#endif // __NODE_H_
