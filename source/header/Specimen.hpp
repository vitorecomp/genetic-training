#ifndef Specimen_H
#define Specimen_H

//includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>

//files
#include "./IOMananger.hpp"

//define

typedef struct timeval time_us;
typedef unsigned long long int ulint;

//namespaces
using namespace std;

class Specimen{
    static uint net_size;
    static uint inputs;
    static uint outputs;
    static uint neuro_size;
    static uint num_neurons;
    static int* types;
    static double **dataset;
    static uint dataset_size;


    double *net;
    double *inter;

    double execute(double*);
public:

    double acuracy;
    Specimen(double**, uint);
    Specimen(string, double**, uint);
    ~Specimen();
    double mimAbsError();
    double mimRelError();
    double mimSquaAbsError();
    double mimSquaRelError();
    string getNeural();
    double testAcuracy();

    void evaluate();
    static bool compare(Specimen&, Specimen&);
    void recreate(Specimen&, Specimen&);
};

#endif
