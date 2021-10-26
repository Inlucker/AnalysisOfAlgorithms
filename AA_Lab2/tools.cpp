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

#define NS_IN_S  1E9


void getCPUTimeOfAlg(AlgPtr alg, int size, int iterations, string alg_name)
{
    mtrx mtrx1;
    mtrx mtrx2;
    mtrx rez;

    prepare(rez, size, size, size, size);
    mtrxGen(mtrx1, size, size, 1000);
    mtrxGen(mtrx2, size, size, 1000);

    double startTime = getCPUTime();
    for (int i = 0; i < iterations; i++)
    {
        alg(rez, mtrx1, size, size, mtrx2, size, size);
    }
    double endTime = getCPUTime();

    double cpu_time = (endTime - startTime);
    //cout << "CPU time of " << alg_name << " with array size " << size << " = " << cpu_time/iterations << endl;
    cout << "(" << size << ", " << cpu_time/iterations << ")";
}

void getStandartTimes()
{
    cout << "CPU time of standartMult() = ";
    for (int i = 100; i <= 1000; i+=100)
        getCPUTimeOfAlg(&standartMult, i, 1000/i, "standartMult");
    cout << endl;
}

void getVinogradTimes()
{
    cout << "CPU time of vinograd() = ";
    for (int i = 100; i <= 1000; i+=100)
        getCPUTimeOfAlg(&vinograd, i, 1000/i, "vinograd");
    cout << endl;
}

void getOptimizedVinogradTimes()
{
    cout << "CPU time of optimizedVinograd() = ";
    for (int i = 100; i <= 1000; i+=100)
        getCPUTimeOfAlg(&optimizedVinograd, i, 1000/i, "optimizedVinograd");
    cout << endl;
}

void getStandartTimesWorst()
{
    cout << "CPU time of standartMult() in worst case = ";
    for (int i = 101; i <= 1001; i+=100)
        getCPUTimeOfAlg(&standartMult, i, 1000/(i-1), "standartMult");
    cout << endl;
}

void getVinogradTimesWorst()
{
    cout << "CPU time of vinograd() in worst case = ";
    for (int i = 101; i <= 1001; i+=100)
        getCPUTimeOfAlg(&vinograd, i, 1000/(i-1), "vinograd");
    cout << endl;
}

void getOptimizedVinogradTimesWorst()
{
    cout << "CPU time of optimizedVinograd() in worst case = ";
    for (int i = 101; i <= 1001; i+=100)
        getCPUTimeOfAlg(&optimizedVinograd, i, 1000/(i-1), "optimizedVinograd");
    cout << endl;
}


void mtrxGen(mtrx &rez, int n, int m, int lim)
{
    for (int i = 0; i < n; i++)
    {
        rez.push_back(vector<int>(m));
        for (int j = 0; j < m; j++)
        {
            rez[i][j] = rand() % lim;
        }
    }
}

int prepare(mtrx &result, int n1, int m1, int n2, int m2)
{
    if (m1 != n2)
    {
        return SIZE_ERROR;
    }
    for (int i = 0; i < n1; i++)
    {
        result.push_back(vector<int>(m2, 0));
    }
    return 0;
}

void printMtrx(mtrx mtr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << mtr[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}
