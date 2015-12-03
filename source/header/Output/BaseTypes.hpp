#ifndef Output_Basetypes
#define Output_Basetypes
//includes
#include <iostream>
#include <string>
//files

//defines
typedef unsigned int uint;

//namespace
using namespace std;

//classes
class Message{
public:
    string box;
    string msg;
    uint line, col;
    Message(uint, uint, string, string);
};

class Screen{
public:
    virtual void print(Message&) = 0;
};

#endif
