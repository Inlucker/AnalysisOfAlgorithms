#include "request.h"

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

void Request::getWords()
{
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
