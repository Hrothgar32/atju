#ifndef __MESSAGE_H_
#define __MESSAGE_H_

enum MSG_TYPE {KILL = 0, PROGRAM, PS, EXIT};

struct Message{
    MSG_TYPE type;
    int pTime;
    char programName[50];
};


#endif // __MESSAGE_H_
