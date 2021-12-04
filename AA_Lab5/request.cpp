#include "request.h"

//using namespace std;
//using namespace chrono;

Request::Request(string _str)
{
    str = _str;
}

/*Request::Request(string str, int task_num, clock_t time)
{
    this->str = str;
    this->task_num = task_num;
    this->time = time;
}*/

#include "Windows.h"

void Request::getWords()
{
    Sleep(1);
    string tmp = "";
    for (auto& c : str)
    {
        if (c != ' ')
            tmp += c;
        else
        {
            words.push_back(tmp);
            tmp = "";
        }
    }
    if (tmp != "")
        words.push_back(tmp);
}

void Request::getPolinoms()
{
    Sleep(1);
    for (auto& w : words)
    {
        bool flag = true;
        int len = w.length();
        int half_len = w.length()/2;
        for (int i = 0; i <= half_len; i++)
            if (w[i] != w[len-1-i])
            {
                flag = false;
                break;
            }
        if (flag)
            polinoms.push_back(w);
    }
}

void Request::getLongestPolinom()
{
    Sleep(1);
    if (polinoms.size() > 0)
        longest_polinom = polinoms[0];
    else
        longest_polinom = "No polinoms";

    for (auto& p : polinoms)
    {
        if (p.length() > longest_polinom.length())
            longest_polinom = p;
    }
}

void Request::calculateTimes()
{
    queue_time1 = pop_time1 - push_time1;
    queue_time2 = pop_time2 - push_time2;
    queue_time3 = pop_time3 - push_time3;
    own_proc_time = processing_time - push_time1;
}
