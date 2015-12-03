#include "../header/GeneticCore.hpp"


GeneticCore::GeneticCore(){}

void GeneticCore::startPopulation(){
    //get arguments
    this->startNumber = io::configs.startNumber;
    this->populationMax = io::configs.maxNumber;
    char **arguments = io::configs.arguments;

    //start the population
    for(unsigned int i = 0; i < this->startNumber; i++)
        specimen_list.push_back(Specimen(arguments[i]));

    //fill the vector
    for(unsigned int i = startNumber; i < this->populationMax; i++)
        specimen_list.push_back(Specimen());

    //print messages
    io::output.printMsgBox("main_messages", "Populacao start sucess");
}
void GeneticCore::run(){
    io::output.printMsgBox("main_messages", "Start running algorithm");
    while(true){
        this->executeAll();
        this->orderByFitness();
        this->recreatePopulation();
        this->printAll();
        if(io::input.isEnded())
            break;
    }
    io::output.printMsgBox("main_messages", "Finish running algorithm");
}

void GeneticCore::generateInformation(){
    io::output.printMsgBox("main_messages", "Generate outputing");
    this->generateFinalResults();
    this->generateCorrelationResults();
    this->generateFullReport();
    io::output.printMsgBox("main_messages", "Finished All, Press Enter to end");
    io::input.waitEnter();
}

void GeneticCore::executeAll(){}
void GeneticCore::orderByFitness(){}
void GeneticCore::recreatePopulation(){}
void GeneticCore::printAll(){}

void GeneticCore::generateFinalResults(){}
void GeneticCore::generateCorrelationResults(){}
void GeneticCore::generateFullReport(){}
