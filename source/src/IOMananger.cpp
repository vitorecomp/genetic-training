#include "../header/IOMananger.hpp"

///////////////////////////////////////////////////////////////////////////////
//Configs
//
///////////////////////////////////////////////////////////////////////////////
Configs io::configs;


Configs::Configs(){
    this->ended = false;
    pthread_mutex_init(&this->m_ended, NULL);
    pthread_cond_init(&this->s_ended, NULL);
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
    pthread_mutex_lock(&m_ended);
    ended = true;
    pthread_mutex_unlock(&m_ended);
    pthread_cond_broadcast(&s_ended);
}

void Configs::waitEnd(){
    pthread_mutex_lock(&m_ended);
	if(!ended)
		pthread_cond_wait(&s_ended, &m_ended);
	pthread_mutex_unlock(&m_ended);
}

///////////////////////////////////////////////////////////////////////////////
//Output
//
///////////////////////////////////////////////////////////////////////////////
Output io::output;

void* run_output(void *arg){
    bool stop = false;
	Output *output = (Output*)arg;
	output->waitSignal();
	output->start();
	while(!stop) {
        stop = output->run();
	}
     pthread_exit(NULL);
}

Output::Output(){
    this->runSignal();
}

void Output::start(){
    io::configs.waitEnd();
}

void Output::runSignal(){
	thread::lockMutex(runMutex_m);
	running = true;
	thread::cond_signal(runSignal_s);
	thread::unlockMutex(runMutex_m);
}

void Output::waitSignal(){
	thread::lockMutex(runMutex_m);
	if(!running)
		thread::cond_wait(runSignal_s, runMutex_m);
	thread::unlockMutex(runMutex_m);
}

bool Output::run(){
    return true;
}
