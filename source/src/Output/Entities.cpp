#include "../../header/Output/Entities.hpp"


MessageBox::MessageBox(string name, uint stx, uint sty, uint sx, uint sy, uint endx){
    this->name = name;

    this->start_x = stx;
    this->start_y = sty;

    this->size_x = sx;
    this->size_y = sy;

    Box::draw(stx, sty, sx, sy);
    Figure::move(start_x, start_y + 5);
    cout << "   ";
    cout << name;
    cout << "   ";
    cout << flush;
}

void MessageBox::print(Message &msg){
    string value = msg.msg;

    if(value.size() <= (size_y-6))
        add_on_list(value);
    else{
        do{
            string value_inter = value.substr(0, size_y - 6);
            add_on_list(value);
            value = value.substr(size_y - 6);
        }while(value.size() <= size_y - 6);
        add_on_list(value);
    }
    printlist();
}

void MessageBox::add_on_list(string msg){
    if(msg_list.size() > (size_x - 6))
        msg_list.pop_front();
    msg_list.push_back(msg);
}


void MessageBox::printlist(){
    Figure::move(start_x + 3, start_y + 3);
    uint j = 3;
    list<string>::iterator i;
    for(i = msg_list.begin();i != msg_list.end(); ++i, j++){
        Figure::move(start_x + j, start_y + 3);
        cout << *i;
        for(uint k = i->size(); k < size_y - 6; k++)
            cout << " ";
        cout << flush;
    }

    Figure::end(endx);
}
