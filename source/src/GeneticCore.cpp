#include "../header/GeneticCore.hpp"


GeneticCore::GeneticCore(){

}

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
    io::output.print(0, 0, "messages", "Populacao start sucess");
}
void GeneticCore::run(){
    io::output.print(1, 0, "messages", "Start running algorithm");
    while(true){
        this->executeAll();
        this->orderByFitness();
        this->recreatePopulation();
        this->printAll();
        if(io::input.isEnded())
            break;
    }
    io::output.print(2, 0, "messages", "Finish running algorithm");
}

void GeneticCore::generateInformation(){
    io::output.print(3, 0, "messages", "Generate outputing");
    this->generateFinalResults();
    this->generateCorrelationResults();
    this->generateFullReport();
    io::output.print(4, 0, "messages", "Finished All, Press Enter to end");
    io::input.waitEnter();
}
