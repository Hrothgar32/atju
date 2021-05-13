#include <mutex>
#include <thread>
#include "rbtree.hpp"
#include "server.hpp"
#include "drawer.hpp"



int main(int argc, char* argv[]){
    // RbTree myTree;
    // int gd=DETECT, gm;
    // initgraph(&gd, &gm, (char*)"");
    // setbkcolor(WHITE);
    // myTree.rbInsert(40);
    // myTree.rbInsert(20);
    // myTree.rbInsert(30);
    // myTree.rbInsert(25);
    // myTree.rbInsert(10);
    // myTree.rbInsert(27);
    // drawTree(myTree, 10);
    // closegraph();
    std::mutex mu;
    RbTree myTree;
    Drawer drawer(&myTree, &mu);
    drawer.init();
    Server myServer(&myTree, &mu, &drawer);
    std::thread serverListenThread(&Server::listen_runnable, &myServer);
    std::thread drawerThread(&Drawer::drawRunnable, &drawer);
    serverListenThread.join();
    drawerThread.join();
    return 0;
    
}
