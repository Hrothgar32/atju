#ifndef __TASK_H_
#define __TASK_H_
#include <string>
#include "node.hpp"

class Task{
    private:
        int pid; // A feladat folyamat azonositoja.
        int x_coord, y_coord; // A feladat koordinatai a megjelenitett faban.
        std::string name;
        Node* treeNode; // A feladat csomopontja a piros-fekete faban;
        bool isRunning;
        int level;
        int vruntime;
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
