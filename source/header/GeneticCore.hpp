#ifndef GeneticCore_H
#define GeneticCore_H

//includes
#include <pthread.h>
#include <iostream>

//files
#include "./IOMananger.hpp"
#include "./Specimen.hpp"

//define

//namespaces
using namespace std;


class GeneticCore{
    void generateFullReport();
    void generateCorrelationResults();
    void generateFinalResults();
    void printAll();


    void recreatePopulation();
    void orderByFitness();
    void executeAll();

    std::vector<Specimen> specimen_list;
    unsigned int startNumber;
    unsigned int populationMax;

public:

    //builder
    GeneticCore();

    //population start
    void startPopulation();

    //runnable
    void run();

    //sumarize the end information
    void generateInformation();

};

#endif
