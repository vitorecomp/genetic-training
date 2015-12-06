#ifndef IOMananger_H
#define IOMananger_H

//includes
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <sstream>

//files
#include "../libs/jsonParser/json.h"
#include "./Output/BaseTypes.hpp"
#include "./Output/Entities.hpp"

//defines

//namespace
using namespace std;

class Configs{
    std::mutex m_ended;
    std::condition_variable s_ended;
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

    uint windows_cols;
    uint windows_lines;

    char **arguments;

    void endSignal();
    void waitEnd();
};

class Output{
private:
    queue<Message> print_queue;
    std::mutex queue_mutex;
    thread *running_thread;

    map<string, Screen*> screen;

public:
    Output();
    ~Output();

    bool run();
    void start();
    void waitSignal();
    void runSignal();

    void print(uint, uint, string, string);
    void printMsgBox(string, string);

    static void setSize(uint, uint);
};

class Input{
private:
public:
    void waitEnter();
    bool isEnded();

    void run();
};

class Logger{
private:
public:
    enum  Type {ERROR, INFO, WARNING};
    void run();
    void log(Type, string);
};

namespace io{
    extern Configs configs;
    extern Output output;
    extern Input input;
    extern Logger logger;
}

void run_output();


#endif
