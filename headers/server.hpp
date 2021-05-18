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

///A folyamatokat kezelő, vizualizációt feladatfuttatással összekötő szerver.
class Server{
    private:
        /// A már inicializált PID-eket számolja.
        int pidCount;
        std::mutex* mutex;
        /// Az éppen feldolgozandó üzenet.
        Message message;
        io_context context;
        udp::endpoint receiver;
        udp::socket serverSocket;
        mutable_buffer buffer;
        err_code ec;
        RbTree* tree;
        Drawer* drawer;
        bool shouldRun;
        /// A szerver által menedzselt feladatok.
        std::unordered_map<int, std::shared_ptr<Task>> tasks;

        /**
         * @brief Beilleszt egy folyamatot menedzseltek közé.
         *
         * @param task A beillesztendő feladatot kezelő mutató
         **/
        void insertTask(const std::shared_ptr<Task>& task);

        /**
         * @brief Eltávolít egy folyamatot a PID-je alapján.
         *
         * A függvény megkeresi a tasks hasítótáblában a folyamatot,
         * majd pedig eltávolítja a piros-fekete fából is.
         *
         * @param pid A folyamat Process ID-ja
         **/
        void removeTask(int pid);

        /**
         * @brief Futtatja a minimális vruntime-al rendelkező folyamatot.
         *
         * A függvény az rbTree popMin metódusát felhasználva megkapja a minimális
         * vruntime-al rendelkező folyamatot, majd pedig "futtatja"
         * --> A task pTime változó ideéig sleepel a folyamatot futtató thread.
         **/
        void runTask();

        /**
         * @brief Frissíti a folyamatok csomópontjait törlés után.
         *
         * Ez a függvény egy szükségszerű megoldás arra az eshetőségre,
         * mikor a fából való törlés a másoló módszer alapján dolgozik:
         * ilyenkor egy Task struktúra treeNode pointere olyan csomópontra mutathat,
         * ami már esetleg törölve volt.
         **/
        void updateOwners();
    public:
        Server(RbTree* tree, std::mutex* mutex, Drawer* drawer);
        void listenRunnable();
        void runTaskRunnable();
};


#endif // __SERVER_H_
