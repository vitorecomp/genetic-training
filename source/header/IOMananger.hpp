#ifndef IOMananger_H
#define IOMananger_H

//includes
#include <iostream>
#include <fstream>
#include <pthread.h>


//files
#include "../libs/jsonParser/json.h"
#include "./Thread.hpp"

//defines

//namespace
using namespace std;

class Configs{
    pthread_mutex_t m_ended;
    pthread_cond_t s_ended;
    bool ended;
public:
    Configs();

    void openFile(char*);
    void setConfigs();

    //variables
    Json::Value json;

    //variavles list
    bool output;
    unsigned int startNumber;
    unsigned int maxNumber;
    char **arguments;

    void endSignal();
    void waitEnd();
};

class Output{
private:
    pthread_t runThread_t;
    pthread_mutex_t runMutex_m;
    pthread_cond_t runSignal_s;
    bool running;
public:
    Output();

    bool run();
    void start();
    void waitSignal();
    void runSignal();

    void print(int, int, string, string);
};

class Input{
private:
public:
    void waitEnter();
    bool isEnded();
};

namespace io{
    extern Configs configs;
    extern Output output;
    extern Input input;
}





#endif
