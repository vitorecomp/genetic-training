#ifndef GeneticCore_H
#define GeneticCore_H

//includes
#include <thread>
#include <mutex>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <cmath>
#include <vector>
#include <sys/time.h>
#include <algorithm>

//files
#include "./IOMananger.hpp"
#include "./Specimen.hpp"

//define

typedef struct timeval time_us;
typedef unsigned long long int ulint;

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
    double min_acuracy;

    //valores internos
    int generation;

    //tempo
    enum Time {START, FINISH, LOCAL, GLOBAL};

    //evaluation
    time_us evaluation_time_start;
    time_us evaluation_time_end;

    ulint evaluation_time_total;

    ulint evaluationTime(Time);

    //order
    time_us order_time_start;
    time_us order_time_end;

    ulint order_time_total;

    ulint orderTime(Time);

    //fusion
    time_us fusion_time_start;
    time_us fusion_time_end;

    ulint fusion_time_total;

    ulint fusionTime(Time);

    //total time
    ulint time_total;
    ulint time_local;
    ulint totalTime(Time);

    //setup time
    time_us setup_time_start;
    time_us setup_time_end;

    ulint setupTime(Time);

    //database
    void openDatabase();
    string database_name;
    double **database;
    uint database_size;

    //output
    ofstream output;
    void openBaseOutput();
    void openFinalFullReport();
    void openFinalResults();

    //acuracy avarange
    double acuracy_avarange;
    double acuracy_variace;
    double correlation_v;

    double acuracyAvarange(Time);
    double acuracyVariace(Time);
    double correlation(Time);

public:

    //builder
    GeneticCore();

    //population start
    void startPopulation();

    //runnable
    void run();

    //sumarize the end information
    void generateInformation();

    //verify convergence
    bool isConveged();
};

#endif
