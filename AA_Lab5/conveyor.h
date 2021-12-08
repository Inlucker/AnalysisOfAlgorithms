#ifndef CONVEYOR_H
#define CONVEYOR_H

#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>

#include <chrono>
#include <Windows.h>

//#include "timer.h"

//using namespace std;
//using namespace chrono;

typedef std::chrono::high_resolution_clock Clock;

#include "request.h"

class Conveyor
{
public:
    Conveyor(int n);

    void process(std::vector<Request> &requests);
    //clock_t process(std::vector<std::string> objvec);

    std::vector<Request> getRes();

private:
    std::vector<std::string> getWords(std::string str);
    std::vector<std::string> getPolinoms(std::vector<std::string> words);
    std::string getLongestPolinom(std::vector<std::string> polinoms);

    void firstBent();
    void secondBent();
    void thirdBent();

    /*void first_conv();
    void second_conv();
    void third_conv();*/

    std::queue<Request> queue1;
    std::queue<Request> queue2;
    std::queue<Request> queue3;

private:
    std::mutex m1, m2, m3, m4;
    int n;
    std::chrono::time_point<Clock> start_time;
    std::vector<Request> res;

    //ADDED
    /*Timer timer;
    clock_t start_t;
    std::mutex resm;

    std::vector<Request> res;*/
};

#endif // CONVEYOR_H
