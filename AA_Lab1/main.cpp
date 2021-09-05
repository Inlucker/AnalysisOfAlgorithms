#include <iostream>
#include <vector>

#include <chrono>
#include <ctime>
#include <Windows.h>

using namespace std;

size_t LevLen(string src, string dst);

size_t LevLenRec(string str1, string str2);

ostream& operator <<(ostream& os, const vector<size_t>& vec);

/*double getCPUTime()
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
}*/

double getCPUTime()
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
}

#define ITERATIONS 1

int main()
{
    string str1 = "arestant";
    string str2 = "dagestan";
    size_t rez = 0;

    auto t_start = std::chrono::high_resolution_clock::now();
    clock_t start = clock();
    double startTime = getCPUTime();

    for (int i = 0; i <= ITERATIONS; i++)
        rez = LevLenRec(str1, str2);

    auto t_end = std::chrono::high_resolution_clock::now();
    clock_t end = clock();
    double endTime = getCPUTime();

    clock_t res  = (end-start);
    double d_res = double(res)/CLOCKS_PER_SEC;
    double cpu_time = (endTime - startTime);

    cout << "Chrono full time = " << std::chrono::duration<double, std::milli>(t_end-t_start).count()/CLOCKS_PER_SEC << endl;
    cout << "Chrono time of LevLen = " << std::chrono::duration<double, std::milli>(t_end-t_start).count()/CLOCKS_PER_SEC/ITERATIONS << endl;

    cout << "Clock full time = " << d_res << endl;
    cout << "Clock time of LevLen = " << d_res/ITERATIONS << endl;

    cout << "CPU time used = " << cpu_time << endl;
    cout << "CPU time of LevLen = " << cpu_time/ITERATIONS << endl;
    //fprintf( stderr, "CPU time used = %lf\n", cpu_time);
    //fprintf( stderr, "CPU time of LevLen = %lf\n", cpu_time/ITERATIONS);


    cout << "length between \"" << str1 << "\" and \"" << str2 << "\" = " << rez << endl;

    return 0;
}

size_t LevLen(string src, string dst)
{
    if (dst.length() < src.length())
    {
        return LevLen(dst, src);
    }

    const size_t min_size = src.length();
    const size_t max_size = dst.length();

    /*cout << "   0| ";
    for (size_t i = 0; i < min_size; i++)
    {
        cout << src[i] << "| ";
    }
    cout << endl;
    for (size_t i = 0; i <= min_size+1; i++)
        cout << "-|-";
    cout << endl;*/

    vector<size_t> cur_row(min_size+1);
    for (size_t i = 1; i <= min_size; i++)
    {
        cur_row[i] = i;
    }

    //cout << "0| ";
    //cout << cur_row;
    for (size_t i = 1; i <= max_size; i++)
    {
        vector<size_t> prev_row = cur_row;
        cur_row = vector<size_t>(min_size+1);
        cur_row[0] = i;
        for (size_t j = 1; j <= min_size; j++)
        {
            size_t add = prev_row[j] + 1;
            size_t del = cur_row[j-1] + 1;
            size_t change = prev_row[j-1];
            if (src[j-1] != dst[i-1])
                change++;
            cur_row[j] = min(add, min(del, change));
        }
        //cout << dst[i-1] << "| ";
        //cout << cur_row;
    }

    return cur_row[min_size];
}

size_t LevLenRec(string str1, string str2)
{
    size_t i = str1.length();
    size_t j = str2.length();
    if (i == 0 && j == 0)
    {
        return 0;
    }
    else if (i > 0 && j == 0)
    {
        return i;
    }
    else if (i == 0 && j > 0)
    {
        return j;
    }
    else
    {
        size_t add = LevLenRec(str1.substr(0, i), str2.substr(0, j-1)) + 1;
        size_t del = LevLenRec(str1.substr(0, i-1), str2.substr(0, j)) + 1;
        size_t change = LevLenRec(str1.substr(0, i-1), str2.substr(0, j-1));
        if (str1[i-1] != str2[j-1])
            change++;
        return  min(add, min(del, change));
    }
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
