#include <iostream>
#include <vector>
//#include <map>

#include <chrono>
#include <ctime>
#include <Windows.h>
#include <limits>

using namespace std;

size_t LevLen(string src, string dst);

size_t LevLenRec(string str1, string str2);

typedef vector<pair<pair<string, string>, size_t>> cash_t;

size_t LevLenRecCash(string str1, string str2, cash_t &cash);

size_t DamLevLen(string src, string dst);

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
    return -1;        // Failed.
}

#define ITERATIONS1 1000
#define ITERATIONS2 10
#define ITERATIONS3 100000

int main()
{
    string str1 = "arsetant";
    string str2 = "dagestan";
    //string str1 = "kot";
    //string str2 = "skto";
    size_t rez = 0;

    //auto t_start = std::chrono::high_resolution_clock::now();
    //clock_t start = clock();
    double startTime = getCPUTime();

    for (int i = 0; i < ITERATIONS1; i++)
    {
        cash_t cash = cash_t();
        rez = LevLenRecCash(str1, str2, cash);
    }

    //auto t_end = std::chrono::high_resolution_clock::now();
    //clock_t end = clock();
    double endTime = getCPUTime();

    //clock_t res  = (end-start);
    //double d_res = double(res)/CLOCKS_PER_SEC;
    double cpu_time = (endTime - startTime);

    //cout << "Chrono full time = " << std::chrono::duration<double, std::milli>(t_end-t_start).count()/CLOCKS_PER_SEC << endl;
    //cout << "Chrono time of LevLen = " << std::chrono::duration<double, std::milli>(t_end-t_start).count()/CLOCKS_PER_SEC/ITERATIONS << endl;

    //cout << "Clock full time = " << d_res << endl;
    //cout << "Clock time of LevLen = " << d_res/ITERATIONS << endl;

    //cout << "CPU time used = " << cpu_time << endl;
    cout << "CPU time of LevLenRecCash = " << cpu_time/ITERATIONS1 << endl;
    //fprintf( stderr, "CPU time used = %lf\n", cpu_time);
    //fprintf( stderr, "CPU time of LevLen = %lf\n", cpu_time/ITERATIONS);


    cout << "length between \"" << str1 << "\" and \"" << str2 << "\" = " << rez << endl;

    cout << endl;

    startTime = getCPUTime();

    for (int i = 0; i < ITERATIONS2; i++)
        rez = LevLenRec(str1, str2);

    endTime = getCPUTime();
    cpu_time = (endTime - startTime);

    //cout << "CPU time used = " << cpu_time << endl;
    cout << "CPU time of LevLenRec = " << cpu_time/ITERATIONS2 << endl;

    cout << "length between \"" << str1 << "\" and \"" << str2 << "\" = " << rez << endl;

    cout << endl;

    startTime = getCPUTime();

    for (int i = 0; i < ITERATIONS3; i++)
        rez = LevLen(str1, str2);

    endTime = getCPUTime();
    cpu_time = (endTime - startTime);

    //cout << "CPU time used = " << cpu_time << endl;
    cout << "CPU time of LevLen = " << cpu_time/ITERATIONS3 << endl;

    cout << "length between \"" << str1 << "\" and \"" << str2 << "\" = " << rez << endl;
    cout << endl;

    startTime = getCPUTime();

    for (int i = 0; i < ITERATIONS3; i++)
        rez = DamLevLen(str1, str2);

    endTime = getCPUTime();
    cpu_time = (endTime - startTime);

    //cout << "CPU time used = " << cpu_time << endl;
    cout << "CPU time of DamLevLen = " << cpu_time/ITERATIONS3 << endl;

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

bool checkCash(string str1, string str2, const cash_t &cash, size_t& rez)
{
    for (auto &el : cash)
    {
        if (el.first.first == str1 && el.first.second == str2)
        {
            rez = el.second;
            return true;
        }
    }
    return false;
}

size_t LevLenRecCash(string str1, string str2, cash_t &cash)
{
    size_t len = INT_MAX;
    if (checkCash(str1, str2, cash, len)) // FIX
    {
        return len;
    }
    //cout << str1 << " " << str2 << endl;
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
        size_t add = LevLenRecCash(str1.substr(0, i), str2.substr(0, j-1), cash) + 1;
        size_t del = LevLenRecCash(str1.substr(0, i-1), str2.substr(0, j), cash) + 1;
        size_t change = LevLenRecCash(str1.substr(0, i-1), str2.substr(0, j-1), cash);
        if (str1[i-1] != str2[j-1])
            change++;

        size_t rez = min(add, min(del, change));
        cash.push_back(make_pair(make_pair(str1, str2), rez));
        return  rez;
    }
}

size_t DamLevLen(string src, string dst)
{
    if (dst.length() < src.length())
    {
        return DamLevLen(dst, src);
    }

    const size_t min_size = src.length();
    const size_t max_size = dst.length();

    vector<size_t> row1(min_size+1);
    for (size_t i = 1; i <= min_size; i++)
    {
        row1[i] = i;
    }

    vector<size_t> row2 = vector<size_t>(min_size+1);

    for (size_t i = 1; i <= max_size; i++)
    {
        if (i >= 2)
        {
            vector<size_t> row3 = row2;
            row2 = row1;
            row1 = vector<size_t>(min_size+1);
            row1[0] = i;
            for (size_t j = 1; j <= min_size; j++)
            {
                size_t add = row2[j] + 1;
                size_t del = row1[j-1] + 1;
                size_t change = row2[j-1];
                if (src[j-1] != dst[i-1])
                    change++;
                row1[j] = min(add, min(del, change));

                if (i > 1 && j > 1 && src[j-1]==dst[i-2] && src[j-2] == dst[i-1])
                {
                    //cout << src[j-1] << " == " << dst[i-2] << "; " << src[j-2] << " == " << dst[i-1] << endl;
                    size_t transposition = row3[j-2] + 1;
                    row1[j] = min(row1[j], transposition);
                }
            }
        }
        else
        {
            row2 = row1;
            row1 = vector<size_t>(min_size+1);
            row1[0] = i;
            for (size_t j = 1; j <= min_size; j++)
            {
                size_t add = row2[j] + 1;
                size_t del = row1[j-1] + 1;
                size_t change = row2[j-1];
                if (src[j-1] != dst[i-1])
                    change++;
                row1[j] = min(add, min(del, change));
            }
        }
    }

    return row1[min_size];
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
