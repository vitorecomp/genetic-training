#include "../../header/Output/BaseTypes.hpp"

Message::Message(uint line, uint col, string box, string msg){
    this->line = line;
    this->col = col;
    this->box = box;
    this->msg = msg;
}
