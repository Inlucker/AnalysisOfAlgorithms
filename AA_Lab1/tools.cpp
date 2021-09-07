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

    //cout << "length between \"" << str1 << "\" and \"" << str2 << "\" = " << rez << endl;

    cout << endl;
}

void getCPUTimeOfAlg(AlgPtr alg, size_t length, int iterations, string alg_name)
{
    string str1 = genStr(length);
    string str2 = genStr(length);
    size_t rez = -1;
    double startTime = getCPUTime();

    for (int i = 0; i < iterations; i++)
        rez = alg(str1, str2);

    double endTime = getCPUTime();

    double cpu_time = (endTime - startTime);
    cout << "CPU time of " << alg_name << " with string length " << length << " = " << cpu_time/iterations << endl;

    cout << endl;
}

void getLevLenTimes()
{
    getCPUTimeOfAlg(&LevLen, 10, ITERATIONS_MATRIX, "LevLen");
    getCPUTimeOfAlg(&LevLen, 20, ITERATIONS_MATRIX/3, "LevLen");
    getCPUTimeOfAlg(&LevLen, 30, ITERATIONS_MATRIX/5, "LevLen");
    getCPUTimeOfAlg(&LevLen, 40, ITERATIONS_MATRIX/8, "LevLen");
    getCPUTimeOfAlg(&LevLen, 50, ITERATIONS_MATRIX/10, "LevLen");
}

void getLevLenRecTimes()
{
    getCPUTimeOfAlg(&LevLenRec, 6, 250, "LevLenRec");
    getCPUTimeOfAlg(&LevLenRec, 7, 25, "LevLenRec");
    getCPUTimeOfAlg(&LevLenRec, 8, 5, "LevLenRec");
    getCPUTimeOfAlg(&LevLenRec, 9, 2, "LevLenRec");
    getCPUTimeOfAlg(&LevLenRec, 10, 1, "LevLenRec");
}

void getLevLenRecCashTimes()
{
    getCPUTimeOfAlg(&LevLenRecCash, 10, ITERATIONS_REC_CASH, "LevLenRecCash");
    getCPUTimeOfAlg(&LevLenRecCash, 20, ITERATIONS_REC_CASH/10, "LevLenRecCash");
    getCPUTimeOfAlg(&LevLenRecCash, 30, ITERATIONS_REC_CASH/50, "LevLenRecCash");
    getCPUTimeOfAlg(&LevLenRecCash, 40, ITERATIONS_REC_CASH/200, "LevLenRecCash");
    getCPUTimeOfAlg(&LevLenRecCash, 50, ITERATIONS_REC_CASH/400, "LevLenRecCash");
}

void getDamLevLenRecTimes()
{
    getCPUTimeOfAlg(&DamLevLenRec, 6, ITERATIONS_REC, "DamLevLenRec");
    getCPUTimeOfAlg(&DamLevLenRec, 7, ITERATIONS_REC/10, "DamLevLenRec");
    getCPUTimeOfAlg(&DamLevLenRec, 8, ITERATIONS_REC/50, "DamLevLenRec");
    getCPUTimeOfAlg(&DamLevLenRec, 9, ITERATIONS_REC/125, "DamLevLenRec");
    getCPUTimeOfAlg(&DamLevLenRec, 10, ITERATIONS_REC/250, "DamLevLenRec");
}

string genStr(size_t size)
{
    string rez = string(size, '0');
    for (size_t i = 0; i < size; i++)
    {
        rez[i] = rand()%26 + 97;
    }
    return rez;
}
