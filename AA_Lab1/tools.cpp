#include "tools.h"

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
