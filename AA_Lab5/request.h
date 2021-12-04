#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;

using namespace chrono;

typedef high_resolution_clock Clock;

class Request
{
public:
    Request(string _str);
    //Request(string _str, int _task_num, clock_t _time);

    void getWords();
    void getPolinoms();
    void getLongestPolinom();

public:
    double push_time1 = -1, pop_time1 = -1;
    double push_time2 = -1, pop_time2 = -1;
    double push_time3 = -1, pop_time3 = -1;
    double processing_time = -1;
//private:
    string str;

    vector<string> words;
    vector<string> polinoms;
    string longest_polinom = "";

    //ADDED
    /*int task_num;
    clock_t time;*/
};

#endif // REQUEST_H
