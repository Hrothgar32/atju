#ifndef __TASK_H_
#define __TASK_H_
#include <string>
#include "node.hpp"

///Egy Unix process megtestesitője.
class Task{
    private:
        /// A feladat folyamat azonosítója.
        int pid;
        /// A feladat koordinátái a megjelenített fában.
        int x_coord, y_coord;
        std::string name;
        /// A feladat csomópontja a piros-fekete fában;
        Node* treeNode;
        /// A feladat szintje a piros-fekete fában.
        int level;
        /// A feladat összes futási ideje.
        int vruntime;
        /// A feladat futási ideje egy iterációban.
        int pTime;
    public:
        Task(int pid, std::string& name, int pTime, int vruntime);
        std::string getName();
        Node* getNode();
        int getPid();
        int getVRuntime();
        void setNode(Node* treeNode);
        void setXCoord(int x_coord);
        void setYCoord(int y_coord);
        void setVRunTime(int vruntime);
        void setLevel(int level);
        int getXCoord();
        int getYCoord();
        void initLevel();
        int getLevel();
        int getPTime();
};


#endif // __TASK_H_
