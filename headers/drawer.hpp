#ifndef __DRAWER_H_
#define __DRAWER_H_
#include <graphics.h>
#include "rbtree.hpp"
#include <memory>
#include <mutex>
#include <task.hpp>
#define HEIGHT 768
#define WIDTH 1024

class Drawer{
    private:
        RbTree* tree;
        std::mutex* mutex;
        std::shared_ptr<Task> currentTask;
        int gd;
        int gm;
        int window;
        bool shouldDraw;
        bool reDraw;
        void draw();
        int treeCToGraphicsC(almtree::COLOR color);
    public:
        Drawer(RbTree* tree, std::mutex* mutex);
        ~Drawer();
        void init();
        void drawRunnable();
        void disableDraw();
        void callReDraw();
        void setRunningTask(std::shared_ptr<Task> currentTask);
};


#endif // __DRAWER_H_
