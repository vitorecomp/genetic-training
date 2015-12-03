//includes
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
//files
#include "./header/IOMananger.hpp"
#include "./header/GeneticCore.hpp"

//defines

//namespaces
using namespace std;

//global


//main
int main(int argc, char *argv[]){
    //verifica a quantidade de argumentos
    if(argc < 2){
        cout << "Por favor, entrar com os argumentos corretamente." << endl;
        cout << "./geneticTraining configFile.json" << endl;
        cout << endl;
        cout << "configFile.json sendo um arquivo que contenha as configurações necessarias" << endl;
        cout << "para executar o programa" << endl;
        exit(1);
    }

    //gera as configuracoes
    io::configs.openFile(argv[1]);
    io::configs.setConfigs();
    thread io_th(run_output);
    //cria core genetico
    GeneticCore genetic_core;

    //cria populacoes
    genetic_core.startPopulation();

    //executa o brain genetico
    genetic_core.run();

    //sumariza informações
    genetic_core.generateInformation();
    io_th.join();
}
