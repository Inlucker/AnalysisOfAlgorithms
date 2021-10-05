#include "tools.h"

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

void getCPUTimeOfAlg(SortPtr alg, int size, int iterations, string alg_name)
{
    int mas[size];
    genMas(size, mas);
    double startTime = getCPUTime();

    for (int i = 0; i < iterations; i++)
    {
        genMas(size, mas);
        alg(&mas[0], &mas[size-1]);
    }

    double endTime = getCPUTime();

    double cpu_time = (endTime - startTime);
    cout << "CPU time of " << alg_name << " with array size " << size << " = " << cpu_time/iterations << endl;

    cout << endl;
}

void getBubbleSortTimes()
{

}

void getSelectionSortTimes()
{

}

void getInsertionSortTimes()
{

}


void genMas(int size, int *mas)
{
    srand(time(0));
    for (int i = 0; i < size; i++)
        mas[i] = rand() % (size*10);
}

