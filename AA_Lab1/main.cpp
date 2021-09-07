#include <iostream>
#include <vector>

#include <chrono>
#include <ctime>
#include <Windows.h>
#include <limits>

using namespace std;

#include "Algorithms.h"


void getCPUTimeOfAlg(AlgPtr alg, string str1, string str2, int iterations, string alg_name = "Algorithm");

ostream& operator <<(ostream& os, const vector<size_t>& vec);

//Более точная
double getCPUTime()
{
    FILETIME createTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;
    if (GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, &kernelTime, &userTime) != -1) {
        ULARGE_INTEGER li = {{userTime.dwLowDateTime, userTime.dwHighDateTime }};
        return li.QuadPart / 10000000.;
    }
    return -1;        // Failed.
}

//Менее точная
/*double getCPUTime()
{
    FILETIME createTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;
    if (GetProcessTimes( GetCurrentProcess( ), &createTime, &exitTime, &kernelTime, &userTime ) != -1)
    {
        SYSTEMTIME userSystemTime;
        if ( FileTimeToSystemTime( &userTime, &userSystemTime ) != -1 )
            return (double)userSystemTime.wHour * 3600.0 +
                (double)userSystemTime.wMinute * 60.0 +
                (double)userSystemTime.wSecond +
                (double)userSystemTime.wMilliseconds / 1000.0;
    }
    return -1;        // Failed.
}*/

#define ITERATIONS_REC_CASH 1000
#define ITERATIONS_REC 10
#define ITERATIONS_MATRIX 100000

void getCPUTimeOfLevLenRec(/*string str1, string str2*/)
{
    string str1 = "arsetant";
    string str2 = "dagestan";
    size_t rez = 0;
    double startTime = getCPUTime();

    for (int i = 0; i < 10; i++)
        rez = LevLenRec(str1, str2);

    double endTime = getCPUTime();

    double cpu_time = (endTime - startTime);
    cout << "CPU time of LevLenRec = " << cpu_time/10 << endl;

    cout << "length between \"" << str1 << "\" and \"" << str2 << "\" = " << rez << endl;

    cout << endl;
}

int main()
{
    string str1 = "arsetant";
    string str2 = "dagestan";
    //string str1 = "kot";
    //string str2 = "skto";

    getCPUTimeOfAlg(&LevLenRecCash, str1, str2, ITERATIONS_REC_CASH, "LevLenRecCash");

    getCPUTimeOfAlg(&LevLenRec, str1, str2, ITERATIONS_REC, "LevLenRec");

    getCPUTimeOfAlg(&LevLen, str1, str2, ITERATIONS_MATRIX, "LevLen");

    getCPUTimeOfAlg(&DamLevLenRec, str1, str2, ITERATIONS_REC, "DamLevLenRec");

    return 0;
}

void getCPUTimeOfAlg(AlgPtr alg, string str1, string str2, int iterations, string alg_name)
{
    size_t rez = 0;
    double startTime = getCPUTime();

    for (int i = 0; i < iterations; i++)
        rez = alg(str1, str2);

    double endTime = getCPUTime();

    double cpu_time = (endTime - startTime);
    cout << "CPU time of " << alg_name << " = " << cpu_time/iterations << endl;

    cout << "length between \"" << str1 << "\" and \"" << str2 << "\" = " << rez << endl;

    cout << endl;
}

ostream& operator <<(ostream& os, const vector<size_t>& vec)
{
    if (vec.size() == 0)
    {
        os << "vector is empty.";
        return os;
    }

    for (auto& el : vec)
    {
        os << el << "| ";
    }
    cout << endl;
    /*for (size_t i = 0; i <= vec.size(); i++)
        os << "-|-";
    cout << endl;*/

    return os;
}
