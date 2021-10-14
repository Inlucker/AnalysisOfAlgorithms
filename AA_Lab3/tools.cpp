#include "tools.h"

double getCPUTime()
{
    FILETIME createTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;
    if ( GetProcessTimes( GetCurrentProcess( ),
        &createTime, &exitTime, &kernelTime, &userTime ) != -1 )
    {
        SYSTEMTIME userSystemTime;
        if ( FileTimeToSystemTime( &userTime, &userSystemTime ) != -1 )
            return (double)userSystemTime.wHour * 3600.0 * 1000.0 +
                (double)userSystemTime.wMinute * 60.0 * 1000.0 +
                (double)userSystemTime.wSecond * 1000.0 +
                (double)userSystemTime.wMilliseconds;
    }
    return -1;        // Failed.
}

#define NS_IN_S  1E9

void getCPUTimeOfAlg(SortPtr alg, GenPtr gen, int size, int iterations, string alg_name)
{
    int mas[iterations][size];
    for (int i = 0; i < iterations; i++)
    {
        gen(size, &mas[i][0]);
    }
    //int mas[size];
    //gen(size, mas);
    double startTime = getCPUTime();
    for (int i = 0; i < iterations; i++)
    {
        alg(&mas[i][0], &mas[i][size-1]);
        //alg(&mas[0], &mas[size-1]);
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
        getCPUTimeOfAlg(&BubbleSort, gen, i, 500000/i, "BubbleSort");
    cout << endl;
}

void getSelectionSortTimes(GenPtr gen)
{
    cout << "CPU time of SelectionSort = ";
    for (int i = 100; i <= 1000; i+=100)
        getCPUTimeOfAlg(&SelectionSort, gen, i, 500000/i, "SelectionSort");
    cout << endl;
}

void getInsertionSortTimes(GenPtr gen)
{
    cout << "CPU time of InsertionSort = ";
    for (int i = 100; i <= 1000; i+=100)
        getCPUTimeOfAlg(&InsertionSort, gen, i, 500000/i, "InsertionSort");
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
