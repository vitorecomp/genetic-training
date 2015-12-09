#include "../header/IOMananger.hpp"

///////////////////////////////////////////////////////////////////////////////
//Configs
//
///////////////////////////////////////////////////////////////////////////////
Configs io::configs;


Configs::Configs(){
    this->ended = false;
    this->ok = true;
}

bool Configs::configOk(){
    return !ok;
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
        this->output = json["output"].asBool();
    else
        this->output = true;


    if(json["windows_cols"] != Json::nullValue)
        this->windows_cols = json["windows_cols"].asInt();
    else
        this->windows_cols = 40;

    if(json["windows_lines"] != Json::nullValue)
        this->windows_lines = json["windows_lines"].asInt();
    else
        this->windows_lines = 40;

    decodeMap();
    this->endSignal();
}

void Configs::decodeMap(){
    if(json["start_number"] != Json::nullValue)
        this->startNumber = json["start_number"].asInt();
    else
        this->startNumber = 2;

    if(json["maxNumber"] != Json::nullValue)
        this->maxNumber = json["maxNumber"].asInt();
    else
        this->maxNumber = 2000;

    if(json["min_acuracy"] != Json::nullValue)
        this->min_acuracy = json["min_acuracy"].asDouble();
    else
        this->min_acuracy = 10;

    if(json["database_name"] != Json::nullValue)
        this->database_name = json["database_name"].asString();
    else
        this->database_name = "./database/normal.csv";


    if(json["seeds"] != Json::nullValue){
        const Json::Value seeds = json["seeds"];
        for ( int index = 0; index < seeds.size(); ++index )  // Iterates over the sequence elements.
            this->seeds.push_back(seeds[index].asString());
    }else{
        this->seeds.push_back("0");
        this->seeds.push_back("1");
    }


    if(json["inputs"] != Json::nullValue)
        this->inputs = json["inputs"].asInt();
    else
        this->inputs = 2;

    if(json["outputs"] != Json::nullValue)
        this->outputs = json["outputs"].asInt();
    else
        this->outputs = 1;

    if(json["num_neurons"] != Json::nullValue)
        this->num_neurons = json["num_neurons"].asInt();
    else
        this->num_neurons = 2;

    types = (int*)calloc(num_neurons, sizeof(int));
    types[0] = 0;
    types[1] = 1;

    threads = 16;
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
    io::output.start();
	while(true) {
        empty = io::output.run();
        io::input.run();
        io::logger.run();

        if(io::input.isEnded() && empty)
            break;
	}
}

Output::Output(){
    this->ended = false;
}


Output::~Output(){
    for (auto& x: screen) {
        delete x.second;
    }
}

void Output::setSize(uint ncols, uint nlines){
    stringstream ss;
    ss << "echo -ne " << "'" << "\e[8;" << nlines << ";" << ncols << "t" << "'";
    system(ss.str().c_str());
}

void Output::start(){
    Output::setSize(io::configs.windows_cols, io::configs.windows_lines);
    Figure::clearAll();
    makeMap();
    this->endSignal();
}

void Output::endSignal(){
    std::unique_lock<std::mutex> lck(m_ended);
    ended = true;
    s_ended.notify_all();
}

void Output::waitEnd(){
    std::unique_lock<std::mutex> lck(m_ended);
    while (!ended)
        s_ended.wait(lck);
}

///////////////funcao que muda
void Output::makeMap(){
    Screen *main_messages = (Screen*) new MessageBox("main_messages", 0, 0, 20, 80, io::configs.windows_lines);
    screen.insert(std::pair<string,Screen*>("main_messages",main_messages) );
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

void Output::printBarGraph(string box, string msg){
    /*
    queue_mutex.lock();
    Message message(0, 0, box, msg);
    this->print_queue.push(message);
    queue_mutex.unlock();
    */
}

void Output::printValues(string box, string msg){
    /*
    queue_mutex.lock();
    Message message(0, 0, box, msg);
    this->print_queue.push(message);
    queue_mutex.unlock();
    */
}


///////////////////////////////////////////////////////////////////////////////
//Input
//
///////////////////////////////////////////////////////////////////////////////
Input io::input;

Input::Input(){
    ended = false;
}

void Input::endSignal(){
    end_mutex.lock();
    ended = true;
    end_mutex.unlock();
}

void Input::waitEnter(){}

void Input::run(){}

bool Input::isEnded(){
    end_mutex.lock();
    bool ended = this->ended;
    end_mutex.unlock();
    return ended;
}

///////////////////////////////////////////////////////////////////////////////
//Input
//
///////////////////////////////////////////////////////////////////////////////
Logger io::logger;

void Logger::run(){}
void Logger::log(Logger::Type, string){}
