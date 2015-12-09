#ifndef Output_Basetypes
#define Output_Basetypes
//includes
#include <iostream>
#include <string>
//files

//defines
typedef unsigned int uint;
#define WALL_PRINT "#"

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

class Figure{
protected:
public:
    static void end(uint x);
    static void move(uint x, uint y);
    static void clearAll();
};

class Box : public Figure{
public:
    static void draw(uint, uint, uint, uint);
};

inline void Figure::move(uint x, uint y){
    cout << "\33[" << x << ";" << y << "H" << flush;
}

inline void Figure::clearAll(){
    cout << "\033c" << flush;
}

inline void Figure::end(uint x){
    move(x, 0);
    cout << flush;
}

#endif
