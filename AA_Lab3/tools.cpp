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

void getCPUTimeOfAlg(SortPtr alg, GenPtr gen, int size, int iterations, string alg_name)
{
    int mas[size];
    gen(size, mas);
    double startTime = getCPUTime();

    for (int i = 0; i < iterations; i++)
    {
        gen(size, mas);
        alg(&mas[0], &mas[size-1]);
    }

    double endTime = getCPUTime();

    double cpu_time = (endTime - startTime);
    //cout << "CPU time of " << alg_name << " with array size " << size << " = " << cpu_time/iterations << endl;
    cout << "(" << size << ", " << cpu_time/iterations << ")";
}

void getBubbleSortTimes(GenPtr gen)
{
    cout << "CPU time of BubbleSort = ";
    for (int i = 100; i <= 1000; i+=100)
        getCPUTimeOfAlg(&BubbleSort, gen, i, 1000000/i, "BubbleSort");
    cout << endl;
}

void getSelectionSortTimes(GenPtr gen)
{
    cout << "CPU time of SelectionSort = ";
    for (int i = 100; i <= 1000; i+=100)
        getCPUTimeOfAlg(&SelectionSort, gen, i, 1000000/i, "SelectionSort");
    cout << endl;
}

void getInsertionSortTimes(GenPtr gen)
{
    cout << "CPU time of InsertionSort = ";
    for (int i = 100; i <= 1000; i+=100)
        getCPUTimeOfAlg(&InsertionSort, gen, i, 1000000/i, "InsertionSort");
    cout << endl;
}

void genMasRandom(int size, int *mas)
{
    srand(time(0));
    for (int i = 0; i < size; i++)
        mas[i] = rand() % (size*10);
}

void genMasWorst(int size, int *mas)
{
    for (int i = 0; i < size; i++)
        mas[i] = size-i;
}

void genMasBest(int size, int *mas)
{
    for (int i = 0; i < size; i++)
        mas[i] = i;
}
