#include "drawer.hpp"
#include <SDL2/SDL_bgi.h>
#include <chrono>
#include <cstdio>
#include <cstring>
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

int Drawer::treeCToGraphicsC(almtree::COLOR color){
    if(color == almtree::RED){
        return RED;
    }
    return BLACK;
}

void Drawer::init(){
    gd = DETECT;
    gm = SDL_1366x768;
    // initwindow(WIDTH, HEIGHT);
    initgraph(&gd, &gm, (char*)"");
    setbkcolor(WHITE);
}

Drawer::~Drawer(){
    closegraph();
}

void Drawer::draw(){
    mutex->lock();
    cleardevice();
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    std::vector<Node*> nodes = tree->getLevelOrder();
    if(!nodes.empty()){
        int beginX = getmaxx()/2;
        int beginY = 30;
        auto task = std::static_pointer_cast<Task>(nodes[0]->data);
        task->setXCoord(beginX);
        task->setYCoord(beginY);
        setcolor(treeCToGraphicsC(nodes[0]->color));
        circle(beginX, beginY, 35);
        setfillstyle(SOLID_FILL, treeCToGraphicsC(nodes[0]->color));
        floodfill(beginX, beginY,treeCToGraphicsC(nodes[0]->color));
        char buffer[20];
        sprintf(buffer, "P:%d,R:%d", task->getPid(), task->getVRuntime());
        setcolor(WHITE);
        outtextxy(task->getXCoord() - 30, task->getYCoord(), buffer);
        int current_level = 1;
        int current_difference = 400;
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
            task->setYCoord(p_y_coord + 80);
            int x_coord = task->getXCoord();
            int y_coord = task->getYCoord();
            setcolor(treeCToGraphicsC(nodes[i]->color));
            circle(x_coord, y_coord, 35);
            setfillstyle(SOLID_FILL, treeCToGraphicsC(nodes[i]->color));
            floodfill(x_coord, y_coord, treeCToGraphicsC(nodes[i]->color));
            setcolor(BLACK);
            line(x_coord, y_coord, p_x_coord, p_y_coord+30);
            char buffer[20];
            sprintf(buffer, "P:%d,R:%d", task->getPid(), task->getVRuntime());
            setcolor(WHITE);
            outtextxy(x_coord - 30, y_coord, buffer);

        }
    }
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    if(currentTask != nullptr){
        char taskMessage[100];
        sprintf(taskMessage, "Currently running is: PID: %d %s with last vruntime of: %d", currentTask->getPid(), currentTask->getName().data(), currentTask->getVRuntime());
        outtextxy(getmaxx()/2 - 200 , getmaxy()-30, taskMessage);
    }
    else{
        char taskMessage[100] = "There is no running task now.";
        outtextxy(getmaxx()/2 - - 120, getmaxy()-30, taskMessage);
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

void Drawer::setRunningTask(std::shared_ptr<Task> currentTask){
    mutex->lock();
    this->currentTask = currentTask;
    mutex->unlock();
}
