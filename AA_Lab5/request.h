#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Request
{
public:
    Request(string _str);

    void getWords();
    void getPolinoms();
    void getLongestPolinom();

public:
    double start_time1, end_time1;
    double start_time2, end_time2;
    double start_time3, end_time3;
    double processing_time;
//private:
    string str;

    vector<string> words;
    vector<string> polinoms;
    string longest_polinom = "";

};

#endif // REQUEST_H
