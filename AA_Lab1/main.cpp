#include <iostream>
#include <vector>
//#include "getCPUTime.h"
#include <Windows.h>

using namespace std;

#define ITERATIONS 1000000

size_t LevLen(string src, string dst);

ostream& operator <<(ostream& os, const vector<size_t>& vec);

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
    return -1;        /* Failed. */
}

int main()
{
    string str1 = "arestant";
    string str2 = "dagestan";
    size_t rez = 0;

    double startTime, endTime;

    startTime = getCPUTime( );
    for (int i = 0; i <= ITERATIONS; i++)
        rez = LevLen(str1, str2);
    endTime = getCPUTime( );

    fprintf( stderr, "CPU time used = %lf\n", (endTime - startTime) );
    fprintf( stderr, "CPU time of LevLen = %lf\n", (endTime - startTime)/ITERATIONS );


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
