#include "../header/GeneticCore.hpp"


GeneticCore::GeneticCore(){}

void GeneticCore::startPopulation(){
    this->generation = 0;

    //get arguments
    this->startNumber = io::configs.startNumber;
    this->populationMax = io::configs.maxNumber;
    this->min_acuracy = io::configs.min_acuracy;
    this->database_name = io::configs.database_name;
    std::vector<string> seeds = io::configs.seeds;

    this->openDatabase();
    this->setupTime(START);
    //start the population
    for(unsigned int i = 0; i < this->startNumber; i++)
        specimen_list.push_back(Specimen(seeds[i], this->database, database_size));

    //fill the vector
    for(unsigned int i = startNumber; i < this->populationMax; i++)
        specimen_list.push_back(Specimen(this->database, database_size));

    //fill the populations
    usleep(1000000);
    for(unsigned int i = startNumber; i < this->populationMax; i++)
        specimen_list[i].recreate(specimen_list[i-1], specimen_list[i-2]);

    this->setupTime(FINISH);
    //print messages
    io::output.printMsgBox("main_messages", "Populacao start sucess");
}

void GeneticCore::run(){
    io::output.printMsgBox("main_messages", "Start running algorithm");
    openBaseOutput();

    while(true){
        this->executeAll();
        this->orderByFitness();
        this->recreatePopulation();
        this->printAll();

        if(this->isConveged())
            break;

        if(io::input.isEnded())
            break;
    }

    output.close();
    io::output.printMsgBox("main_messages", "Finish running algorithm");
}

void GeneticCore::generateInformation(){
    io::output.printMsgBox("main_messages", "Generate outputing");
    this->generateFinalResults();
    this->generateFullReport();
    io::output.printMsgBox("main_messages", "Finished All, Press Enter to end");
    io::input.waitEnter();
    io::input.endSignal();
}

void GeneticCore::executeAll(){
    evaluationTime(START);
    for(uint i = 0; i < specimen_list.size(); i++)
        specimen_list[i].evaluate();
    evaluationTime(FINISH);
}

void GeneticCore::orderByFitness(){
    orderTime(START);
    std::sort(specimen_list.begin(), specimen_list.end(), Specimen::compare);
    orderTime(FINISH);
}

void GeneticCore::recreatePopulation(){
    fusionTime(START);
    uint dist = 0;
    uint max = specimen_list.size();
    for(unsigned int i = specimen_list.size() - 1; i > ceil(((double)2 * specimen_list.size())/3); i--){
        dist = (max - i) * 2;
        specimen_list[i].recreate(specimen_list[dist], specimen_list[dist + 1]);
    }
    fusionTime(FINISH);
}

void GeneticCore::printAll(){
    //print data
    this->generation++;
    stringstream ss;
    ss << "Finish Generation number: " << generation;
    io::output.printMsgBox("main_messages", ss.str());

    ss.str("");
    ss << specimen_list[0].acuracy/this->min_acuracy;
    io::output.printMsgBox("main_messages", ss.str());
    io::output.printBarGraph("progress_bar", ss.str());

    io::output.printValues("main_messages", "0 / 0 / 0 / 0");

    //generation line
    ss.str("");
    ss << generation << ";";
    ss << evaluationTime(LOCAL) << ";";
    ss << orderTime(LOCAL) << ";";
    ss << fusionTime(LOCAL) << ";";
    ss << totalTime(LOCAL) << ";";

    ss << correlation(LOCAL) << ";";
    ss << specimen_list[0].acuracy << ";";
    ss << acuracyAvarange(LOCAL) << ";";
    ss << acuracyVariace(LOCAL);

    ss << endl;

    output << ss.str();
}

bool GeneticCore::isConveged(){
    if(specimen_list[0].acuracy < this->min_acuracy)
        return true;
    return false;
}


void GeneticCore::generateFinalResults(){
    openFinalResults();
    stringstream ss;
    ss << "{" << endl;
    ss << "\t \"Neural_Network\":" << specimen_list[0].getNeural() << "," << endl;
    ss << "\t \"generation\":" << generation << ","<< endl;
    ss << endl;
    ss << "\t \"acuracy\":" << specimen_list[0].acuracy << ","<< endl;
    ss << "\t \"acuracy_test\":" << specimen_list[0].testAcuracy() << ",";

    ss << endl;
    ss << "\t \"error_minimo_absoluto\":" << specimen_list[0].mimAbsError() << ","<< endl;
    ss << "\t \"erro_minimo_quadradico_absoluto\":" << specimen_list[0].mimSquaAbsError() << ",";
    ss << "\t \"error_minimo_relativo\":" << specimen_list[0].mimRelError() << ",";
    ss << "\t \"error_minimo_quadradico_relativo\":" << specimen_list[0].mimSquaRelError();
    ss << endl;
    ss << "}";
    ss << endl;

    output << ss.str();
    output.close();
}

void GeneticCore::generateFullReport(){
    openFinalFullReport();

    stringstream ss;

    ss << "{" << endl;
    ss << "\t \"generations\":" << generation << "," << endl;
    ss << "\t \"evaluation_time\":" << evaluationTime(GLOBAL) << ","<< endl;
    ss << "\t \"order_time\":" << orderTime(GLOBAL) << ","<< endl;
    ss << "\t \"fusion_time\":" << fusionTime(GLOBAL) << ","<< endl;
    ss << "\t \"total_time\":" << totalTime(GLOBAL) << ","<< endl;
    ss << "\t \"setup_time\":" << setupTime(GLOBAL) << ","<< endl;
    ss << endl;
    ss << "\t \"correlation\":" << correlation(GLOBAL) << ",";
    ss << "\t \"acuracia final\":" << specimen_list[0].acuracy << ",";
    ss << "\t \"acuracy_avarange\":" << acuracyAvarange(GLOBAL) << ",";
    ss << "\t \"acuracy_variace\":" << acuracyVariace(GLOBAL);
    ss << endl;
    ss << "}";
    ss << endl;

    output << ss.str();
    output.close();
}

void GeneticCore::openDatabase(){
    ifstream myfile;
    myfile.open(database_name, std::ifstream::in);
    uint valores = io::configs.inputs + io::configs.outputs;

    double* inter;
    database_size = 0;
    string line;
    //get the string
    if (myfile.is_open()){
        while(getline (myfile,line)){
            database_size++;

            if(database_size == 1)
                database = (double**)calloc(database_size, sizeof(double*));
            else
                database = (double**)realloc(database, database_size * sizeof(double*));

            inter = (double*)calloc(valores, sizeof(double));
            database[database_size -1] = inter;

            for(uint i = 0; i < valores - 1; i++){
                std::size_t found = line.find(";");
                if (found==std::string::npos)
                    throw std::invalid_argument("Arquivo invalido entrada");

                inter[i] = stod(line.substr(0, found));
                line = line.substr(found+1);
            }

            inter[valores-1] = stod(line);
        }
        myfile.close();
    }else{
        throw std::invalid_argument("Arquivo não encontrado");
    }
}

void GeneticCore::openBaseOutput(){}
void GeneticCore::openFinalFullReport(){}
void GeneticCore::openFinalResults(){}

ulint GeneticCore::evaluationTime(Time){}
ulint GeneticCore::orderTime(Time){}
ulint GeneticCore::fusionTime(Time){}
ulint GeneticCore::totalTime(Time){}
ulint GeneticCore::setupTime(Time){}

double GeneticCore::correlation(Time){}
double GeneticCore::acuracyAvarange(Time){}
double GeneticCore::acuracyVariace(Time){}
