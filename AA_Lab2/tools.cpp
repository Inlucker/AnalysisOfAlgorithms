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

/*void getCPUTimeOfAlg(SortPtr alg, GenPtr gen, int size, int iterations, string alg_name)
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
}*/

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
