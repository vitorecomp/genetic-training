#ifndef MessegeBox_H
#define MessegeBox_H

//includes
#include <iostream>
#include <string>
#include <list>
//files
#include "BaseTypes.hpp"

//defines
typedef unsigned int uint;

//namespace
using namespace std;

class MessageBox : public Screen{
    string name;
    uint start_x, start_y, size_x, size_y, endx;

    list<string> msg_list;

    void add_on_list(string);
    void printlist();
public:
    MessageBox(string, uint, uint, uint, uint, uint);

    void print(Message&);
};


#endif
