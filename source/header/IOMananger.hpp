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
    bool ok;

    void decodeMap();
public:
    Configs();

    void openFile(char*);
    void setConfigs();

    bool configOk();
    string error_msg;

    //variables
    Json::Value json;

    //variavles list
    bool output;

    //io
    uint windows_cols;
    uint windows_lines;


    //problem
    unsigned int startNumber;
    unsigned int maxNumber;
    vector<string> seeds;
    double min_acuracy;
    string database_name;

    //neuron
    uint num_neurons;
    uint outputs;
    uint inputs;
    int *types;

    //parallel
    uint threads;

    void endSignal();
    void waitEnd();
};

class Output{
private:
    std::mutex m_ended;
    std::condition_variable s_ended;
    bool ended;

    queue<Message> print_queue;
    std::mutex queue_mutex;
    thread *running_thread;

    void makeMap();
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
    void printBarGraph(string, string);
    void printValues(string, string);

    static void setSize(uint, uint);

    void endSignal();
    void waitEnd();
};

class Input{
private:
    std::mutex end_mutex;
    bool ended;
public:
    Input();

    void waitEnter();
    bool isEnded();

    void endSignal();

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
