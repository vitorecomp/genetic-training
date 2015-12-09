//includes
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <sstream>

//files

//defines
#define CONST 127
#define MAX 1500000000
#define THREADS 32

//namespaces
using namespace std;
typedef unsigned long long int ullint;


//global

ullint time_to_int(struct timeval start, struct timeval end){
    return 	((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
}

void linear(uint final){
    for(uint i = 0; i < final; i++){
        usleep(0.27 * 100);
    }
}

void quadradic(uint final){
    for(uint i = 0; i < final * final; i++){
        usleep(0.74 * 100);
    }
}

void logaritmic(uint final){
    for(uint i = 0; i < log(final*100); i++){
        usleep(0.38 * 100);
    }
}

void expotencial(uint final){
    for(uint i = 0; i < pow(final, final); i++){
        usleep(0.83 * 100);
    }
}

//main
int main(int argc, char *argv[]){
    struct timeval start;
    gettimeofday(&start, NULL);
    std::ofstream file;
    file.open("./database/complete.csv", std::ofstream::out);
    std::mutex t_mutex;


    #pragma omp parallel for num_threads(THREADS)
    for(int i = 0; i < 100000;i++){
        struct timeval end;
        gettimeofday(&end, NULL);
        ullint totali = time_to_int(start, end);
        if(totali > MAX)
            continue;

        struct timeval start_tim, end_tim;
        gettimeofday(&start_tim, NULL);
        uint quadradic_v = rand()%100;
        uint logaritmic_v = rand()%10 * 100;
        uint linear_v = rand()%100;
        uint expotencial_v = rand()%5;


        quadradic(quadradic_v*0.2);
        logaritmic(logaritmic_v * 0.93);
        linear(linear_v * 0.8);
        expotencial(expotencial_v * 0.7);

        gettimeofday(&end_tim, NULL);
        ullint total = time_to_int(start_tim, end_tim);
        t_mutex.lock();
        cout << quadradic_v << ";";
        cout << logaritmic_v << ";";
        cout << linear_v << ";" ;
        cout << expotencial_v << ";";
        cout << total << endl;

        file << quadradic_v << ";";
        file << logaritmic_v << ";";
        file << linear_v << ";" ;
        file << expotencial_v << ";";
        file << total << endl;

        t_mutex.unlock();
    }
    file.close();

    cout << "Teste2" << endl;

    file.open("./database/normal.csv", std::ofstream::out);
    #pragma omp parallel for num_threads(THREADS)
    for(int i = 0; i < 10000;i++){
        uint quadradic_v = (i - i%100)/100 * 0.35;
        uint linear_v = i%100 * 0.43;

        t_mutex.lock();
        cout << (i - i%100)/100 << ";" << i%100 << ";" << (quadradic_v * quadradic_v)*0.25*100 + linear_v*0.47*100 << endl;
        file << (i - i%100)/100 << ";" << i%100 << ";" << (quadradic_v * quadradic_v)*0.25*100 + linear_v*0.47*100 << endl;
        t_mutex.unlock();
    }
    file.close();


    file.open("./database/no_error.csv", std::ofstream::out);
    #pragma omp parallel for num_threads(THREADS)
    for(int i = 0; i < 100000;i++){
        uint quadradic_v = rand()%100;
        uint logaritmic_v = rand()%10 * 100;
        uint linear_v = rand()%100;
        uint expotencial_v = rand()%5;

        uint linear_i = linear_v * 0.27;
        uint quadradic_i = quadradic_v * 0.93;
        uint logaritmic_i = linear_v * 0.8;
        uint expotencial_i = expotencial_v * 0.7;

        uint total = linear_v * 0.27 * 100;
        total += quadradic_v * quadradic_v * 0.74 * 100;
        total += log(logaritmic_v) * 0.38 * 100;
        total += pow(expotencial_v, expotencial_v) * 0.83 * 100;

        t_mutex.lock();
        cout << quadradic_v << ";" << logaritmic_v << ";" << linear_v << ";" << expotencial_v << ";" << total << endl;
        file << quadradic_v << ";" << logaritmic_v << ";" << linear_v << ";" << expotencial_v << ";" << total << endl;
        t_mutex.unlock();
    }
    file.close();
}
