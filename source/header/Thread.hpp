#ifndef THREAD_H
#define THREAD_H

#include <string>
#include <iostream>

#include <pthread.h>

namespace thread {
    int static threadInit(pthread_t& thread, const pthread_attr_t* attr, void *(*start_routine)(void*), void* arg);

	int static initMutex(pthread_mutex_t& mutex);
	int static lockMutex(pthread_mutex_t& mutex);
	int static unlockMutex(pthread_mutex_t& mutex);

	int static cond_init(pthread_cond_t& cond);
	int static cond_signal(pthread_cond_t& cond);
	int static cond_wait(pthread_cond_t& cond, pthread_mutex_t& mutex);
}

using namespace thread;
void* run_thread(void*);

/*************************************************/
/* To use Thread you need to implement run and   */
/* execute runSignal() on your class constructor */
/*************************************************/
class Thread{
protected:
    static uint id_th;
    pthread_t runThread_t;
    pthread_mutex_t runMutex_m;
    pthread_cond_t runSignal_s;
    bool running;
public:
    Thread();
    virtual void run() = 0;
    void runSignal();
    void waitSignal();
};


inline int  thread::threadInit(pthread_t& thread, const pthread_attr_t* attr, void *(*start_routine)(void*), void* arg){
	return pthread_create(&thread, attr, start_routine, arg);
};

inline int  thread::initMutex(pthread_mutex_t& mutex){
    return pthread_mutex_init(&mutex, NULL);
};


inline int  thread::lockMutex(pthread_mutex_t& mutex){
    return pthread_mutex_lock(&mutex);
};

inline int  thread::unlockMutex(pthread_mutex_t& mutex){
    return pthread_mutex_unlock(&mutex);
};

inline int  thread::cond_init(pthread_cond_t& cond){
    return pthread_cond_init(&cond, NULL);
};

inline int  thread::cond_signal(pthread_cond_t& cond){
    return pthread_cond_signal(&cond);
};

inline int  thread::cond_wait(pthread_cond_t& cond, pthread_mutex_t& mutex){
    return pthread_cond_wait(&cond, &mutex);
};


#endif
