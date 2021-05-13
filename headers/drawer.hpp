#ifndef __DRAWER_H_
#define __DRAWER_H_
#include <graphics.h>
#include "rbtree.hpp"
#include <mutex>

class Drawer{
    private:
        RbTree* tree;
        std::mutex* mutex;
        int gd;
        int gm;
        bool shouldDraw;
        bool reDraw;
        _color treeCToGraphicsC(almtree::COLOR color);
    public:
        Drawer(RbTree* tree, std::mutex* mutex);
        ~Drawer();
        void init();
        void drawRunnable();
        void draw();
        void disableDraw();
        void callReDraw();
};


#endif // __DRAWER_H_
