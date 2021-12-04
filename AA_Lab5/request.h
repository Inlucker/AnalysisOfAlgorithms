#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

//typedef std::chrono::high_resolution_clock Clock;

using namespace std;

using namespace chrono;

class Request
{
public:
    Request(string _str);

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

};

#endif // REQUEST_H
