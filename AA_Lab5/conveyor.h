#ifndef CONVEYOR_H
#define CONVEYOR_H

#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>

using namespace std;

#include "request.h"

class Conveyor
{
public:
    Conveyor(int n);

    void process(vector<Request> &requests);

private:
    vector<string> getWords(string str);
    vector<string> getPolinoms(vector<string> words);
    string getLongestPolinom(vector<string> polinoms);

    void firstBent();
    void secondBent();
    void thirdBent();

    queue<Request> queue1;
    queue<Request> queue2;
    queue<Request> queue3;

private:
    mutex m1, m2, m3;

    int n;
};

#endif // CONVEYOR_H
