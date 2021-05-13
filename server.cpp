#include "server.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <utility>
#include "asio/buffer.hpp"
#include "message.h"
#include "node.hpp"
#include "task.hpp"
#include "drawer.hpp"

Server::Server(RbTree* tree, std::mutex* mutex, Drawer* drawer) : receiver(udp::v4(), PORT), serverSocket(context, receiver), buffer(&message, sizeof(message)){
    this->tree = tree;
    this->mutex = mutex;
    this->drawer = drawer;
    shouldRun = true;
    pidCount = 0;
}

void Server::insertTask(const std::shared_ptr<Task>& task){
    mutex->lock();
    Node* taskToInsert = tree->rbInsert(task->getVRuntime());
    taskToInsert->data = task;
    task->setNode(taskToInsert);
    task->initLevel();
    mutex->unlock();
}

void Server::removeTask(int pid){
    mutex->lock();
    auto task = tasks.find(pid);
    tree->rbDelete(task->second->getNode());
    tasks.erase(pid);
    updateOwners();
    mutex->unlock();
}

void Server::listen_runnable(){
    while(shouldRun){
        udp::endpoint sender;
        serverSocket.receive_from(asio::buffer(buffer), sender);
        switch(message.type){
            case KILL:{
                removeTask(message.pTime);
                drawer->callReDraw();
                break;
            }
            case PROGRAM:{
                pidCount++;
                std::string programName(message.programName);
                auto newTask = std::make_shared<Task>(pidCount, programName, message.pTime, pidCount);
                tasks.insert(std::make_pair(pidCount, newTask));
                insertTask(newTask);
                drawer->callReDraw();
                break;
            }
            case PS:
                break;
            case EXIT:
                shouldRun = false;
                drawer->disableDraw();
        }
    }
}

void Server::updateOwners(){
    std::vector<Node*> treeNodes = tree->getLevelOrder();
    for(auto& i : treeNodes){
        auto task = std::static_pointer_cast<Task>(i->data);
        if(task->getNode() != i)
            task->setNode(i);
    }
}
