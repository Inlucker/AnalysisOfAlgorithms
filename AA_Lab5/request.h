#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

//using namespace std;
//using namespace chrono;

typedef std::chrono::high_resolution_clock Clock;

class Request
{
public:
    Request(std::string _str);
    //Request(std::string _str, int _task_num, clock_t _time);

    void getWords();
    void getPolinoms();
    void getLongestPolinom();

    void calculateTimes();

public:
    double push_time1 = -1, pop_time1 = -1;
    double push_time2 = -1, pop_time2 = -1;
    double push_time3 = -1, pop_time3 = -1;
    double processing_time = -1;

    double queue_time1 = -1;
    double queue_time2 = -1;
    double queue_time3 = -1;

    double own_proc_time = -1;
//private:
    std::string str;

    std::vector<std::string> words;
    std::vector<std::string> polinoms;
    std::string longest_polinom = "";

    //ADDED
    /*int task_num;
    clock_t time;*/
};

#endif // REQUEST_H
