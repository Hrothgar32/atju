#include "drawer.hpp"
#include <chrono>
#include <graphics.h>
#include <memory>
#include <thread>
#include "task.hpp"

Drawer::Drawer(RbTree* tree, std::mutex* mutex){
    this->tree = tree;
    this->mutex = mutex;
    shouldDraw = true;
    reDraw = false;
}

_color Drawer::treeCToGraphicsC(almtree::COLOR color){
    if(color == almtree::RED){
        return RED;
    }
    return BLACK;
}

void Drawer::init(){
    gd = DETECT;
    initgraph(&gd, &gm, (char*)"");
    setbkcolor(WHITE);
}

Drawer::~Drawer(){
    closegraph();
}

void Drawer::draw(){
    mutex->lock();
    cleardevice();
    setfontcolor(WHITE);
    std::vector<Node*> nodes = tree->getLevelOrder();
    if(!nodes.empty()){
        int beginX = getmaxx()/2;
        int beginY = 20;
        auto task = std::static_pointer_cast<Task>(nodes[0]->data);
        task->setXCoord(beginX);
        task->setYCoord(beginY);
        setcolor(treeCToGraphicsC(nodes[0]->color));
        circle(beginX, beginY, 20);
        floodfill(beginX, beginY,treeCToGraphicsC(nodes[0]->color));
        char buffer[5];
        sprintf(buffer, "%d", task->getPid());
        outtextxy(task->getXCoord() - 5, task->getYCoord(), buffer);
        int current_level = 1;
        int current_difference = 150;
        for(int i = 1; i < nodes.size(); i++){
            task = std::static_pointer_cast<Task>(nodes[i]->data);
            auto parent_task = std::static_pointer_cast<Task>(nodes[i]->parent->data);
            int p_x_coord = parent_task->getXCoord();
            int p_y_coord = parent_task->getYCoord();
            if(task->getLevel() > current_level){
                current_level++;
                current_difference /= 2;
            }
            if(nodes[i]->isOnLeft()){
                task->setXCoord(p_x_coord - current_difference);
            }
            else{
                task->setXCoord(p_x_coord + current_difference);
            }
            task->setYCoord(p_y_coord + 70);
            int x_coord = task->getXCoord();
            int y_coord = task->getYCoord();
            setcolor(treeCToGraphicsC(nodes[i]->color));
            circle(x_coord, y_coord, 20);
            floodfill(x_coord, y_coord, treeCToGraphicsC(nodes[i]->color));
            setcolor(BLACK);
            line(x_coord, y_coord, p_x_coord, p_y_coord+20);
            char buffer[5];
            sprintf(buffer, "%d", task->getPid());
            outtextxy(x_coord - 5, y_coord, buffer);

        }
        setfontcolor(BLACK);
        outtextxy(getmaxx()/2 - 40, getmaxy()-30, (char*)"Random szoveg");
    }
    reDraw = false;
    mutex->unlock();
}

void Drawer::disableDraw(){
    mutex->lock();
    shouldDraw = false;
    mutex->unlock();
}

void Drawer::callReDraw(){
    mutex->lock();
    reDraw = true;
    mutex->unlock();
}

void Drawer::drawRunnable(){
    while(shouldDraw){
        if(reDraw)
            draw();
    }
}
