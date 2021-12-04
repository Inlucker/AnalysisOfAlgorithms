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

#include "timer.h"

using namespace std;

using namespace chrono;

typedef std::chrono::high_resolution_clock Clock;

#include "request.h"

class Conveyor
{
public:
    Conveyor(int n);

    void process(vector<Request> &requests);
    //clock_t process(vector<string> objvec);

private:
    vector<string> getWords(string str);
    vector<string> getPolinoms(vector<string> words);
    string getLongestPolinom(vector<string> polinoms);

    void firstBent();
    void secondBent();
    void thirdBent();

    /*void first_conv();
    void second_conv();
    void third_conv();*/

    queue<Request> queue1;
    queue<Request> queue2;
    queue<Request> queue3;

private:
    mutex m1, m2, m3;
    int n;
    time_point<high_resolution_clock> start_time;

    //ADDED
    /*Timer timer;
    clock_t start_t;
    mutex resm;

    vector<Request> res;*/
};

#endif // CONVEYOR_H
