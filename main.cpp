#include <mutex>
#include <thread>
#include "rbtree.hpp"
#include "server.hpp"
#include "drawer.hpp"


int main(int argc, char* argv[]){
    std::mutex mu;
    RbTree myTree;
    Drawer drawer(&myTree, &mu);
    drawer.init();
    Server myServer(&myTree, &mu, &drawer);
    std::thread serverListenThread(&Server::listenRunnable, &myServer);
    std::thread drawerThread(&Drawer::drawRunnable, &drawer);
    std::thread taskRunnerThread(&Server::runTaskRunnable, &myServer);
    serverListenThread.join();
    drawerThread.join();
    taskRunnerThread.join();
    return 0;
    
}
