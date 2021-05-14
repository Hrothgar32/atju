#include "task.hpp"
#include <memory>

Task::Task(int pid, std::string& name, int pTime, int vruntime){
    this->pid = pid;
    this->name = name;
    this->pTime = pTime;
    this->vruntime = vruntime;
    treeNode = nullptr;
    isRunning = false;
    level = x_coord = y_coord = 0;
}

Node* Task::getNode(){
    return treeNode;
}

std::string Task::getName(){
    return name;
}

void Task::setNode(Node* treeNode){
    this->treeNode = treeNode;
}

void Task::setVRunTime(int vruntime){
    this->vruntime = vruntime;
}

int Task::getPid(){
    return pid;
}

void Task::initLevel(){
    Node* parent = treeNode->parent;
    if(parent != nullptr){
        auto upperTask = std::static_pointer_cast<Task>(parent->data);
        level = upperTask->level + 1;
    }
}

void Task::setXCoord(int x_coord){
    this->x_coord = x_coord;
}

int Task::getLevel(){
    return level;
}

void Task::setLevel(int level){
    this->level = level;
}

void Task::setYCoord(int y_coord){
    this->y_coord = y_coord;
}

int Task::getXCoord(){
    return x_coord;
}

int Task::getYCoord(){
    return y_coord;
}

int Task::getVRuntime(){
    return vruntime;
}

int Task::getPTime(){
    return pTime;
}
