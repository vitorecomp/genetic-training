#include "../header/IOMananger.hpp"

///////////////////////////////////////////////////////////////////////////////
//Configs
//
///////////////////////////////////////////////////////////////////////////////
Configs io::configs;


Configs::Configs(){
    this->ended = false;
}


void Configs::openFile(char *name){
    string line;
    stringstream ss;
    //open the text
    ifstream myfile;
    myfile.open(name, std::ifstream::in);

    //get the string
    if (myfile.is_open()){
        while(getline (myfile,line))
            ss << line << '\n';
        myfile.close();
    }else{
        throw std::invalid_argument("Json File invalid");
    }

    //validate the input
    string json = ss.str();
    if(json.length() == 0)
        throw std::invalid_argument("Json File invalid");


    //parse the string
    Json::Value value;
    Json::Reader reader;

    bool parsed = reader.parse(json, value);
    if(!parsed)
        throw std::invalid_argument("Json File invalid");

    //configure from json
    this->json = value;
}

void Configs::setConfigs(){
    if(json["output"] != Json::nullValue)
        this->output = json["low_port"].asBool();
    else
        this->output = true;

    this->endSignal();
}


void Configs::endSignal(){
    std::unique_lock<std::mutex> lck(m_ended);
    ended = true;
    s_ended.notify_all();
}

void Configs::waitEnd(){
    std::unique_lock<std::mutex> lck(m_ended);
    while (!ended)
        s_ended.wait(lck);
}

///////////////////////////////////////////////////////////////////////////////
//Output
//
///////////////////////////////////////////////////////////////////////////////
Output io::output;

void run_output(){
    io::configs.waitEnd();
    bool empty = false;
	while(true) {
        empty = io::output.run();
        io::input.run();

        if(io::input.isEnded() && empty)
            break;
	}
}

Output::Output(){
    this->setSize();
    Screen *main_messages = (Screen*)MessegeBox("main_messages", 0, 0, 20, 10);
}
Output::~Output(){}

void Output::start(){
}

bool Output::run(){
    queue_mutex.lock();

    if(print_queue.empty()){
        queue_mutex.unlock();
        return true;
    }

    Message message = print_queue.front();
    print_queue.pop();

    queue_mutex.unlock();

    if(screen.find(message.box) != screen.end())
        this->screen[message.box]->print(message);
    else
        io::logger.log(Logger::ERROR, "Mapa de screen não encontrado");
    return false;
}

void Output::printMsgBox(string box, string msg){
    queue_mutex.lock();
    Message message(0, 0, box, msg);
    this->print_queue.push(message);
    queue_mutex.unlock();
}


///////////////////////////////////////////////////////////////////////////////
//Input
//
///////////////////////////////////////////////////////////////////////////////
Input io::input;

void Input::waitEnter(){}

void Input::run(){}

bool Input::isEnded(){}

///////////////////////////////////////////////////////////////////////////////
//Input
//
///////////////////////////////////////////////////////////////////////////////
Logger io::logger;

void Logger::run(){}
void Logger::log(Logger::Type, string){}
