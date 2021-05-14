#ifndef __SERVER_H_
#define __SERVER_H_
#include <memory>
#define PORT 5000
#include <asio.hpp>
#include <mutex>
#include "message.h"
#include "rbtree.hpp"
#include "task.hpp"
#include "drawer.hpp"

using err_code = asio::error_code;
using err_code = asio::error_code;
using udp = asio::ip::udp;
using io_context = asio::io_context;
using asio::mutable_buffer;

class Server{
    private:
        int pidCount;
        std::mutex* mutex;
        Message message;
        io_context context;
        udp::endpoint receiver;
        udp::socket serverSocket;
        mutable_buffer buffer;
        err_code ec;
        RbTree* tree;
        Drawer* drawer;
        bool shouldRun;
        std::unordered_map<int, std::shared_ptr<Task>> tasks;
        void insertTask(const std::shared_ptr<Task>& task);
        void removeTask(int pid);
        void runTask();
        void updateOwners();
    public:
        Server(RbTree* tree, std::mutex* mutex, Drawer* drawer);
        void listenRunnable();
        void runTaskRunnable();
};


#endif // __SERVER_H_
