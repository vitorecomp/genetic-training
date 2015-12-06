#include "../../header/Output/BaseTypes.hpp"

Message::Message(uint line, uint col, string box, string msg){
    this->line = line;
    this->col = col;
    this->box = box;
    this->msg = msg;
}

void Box::draw(uint start_x, uint start_y, uint size_x, uint size_y){
    move(start_x, start_y);
    for(uint i = 0; i < size_y; i++)
        cout << WALL_PRINT;

    uint fim = start_y + size_y;
    for(uint i = 0; i < size_x; i++){
        move(start_x + i, start_y);
        cout << WALL_PRINT;
        move(start_x + i, fim);
        cout << WALL_PRINT;
    }

    move(start_x + size_x, start_y);
    for(uint i = 0; i < size_y; i++)
        cout << WALL_PRINT;

    cout << endl;
}
