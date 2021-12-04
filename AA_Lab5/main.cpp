#include <iostream>
#include <string.h>
#include <vector>
#include <random>

using namespace std;

vector<string> getWords(string str)
{
    vector<string> rez;

    string tmp = "";
    for (auto& c : str)
    {
        if (c != ' ')
            tmp += c;
        else
        {
            rez.push_back(tmp);
            tmp = "";
        }
    }
    if (tmp != "")
        rez.push_back(tmp);

    return rez;
}

vector<string> getPolinoms(vector<string> words)
{
    vector<string> rez;

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
            rez.push_back(w);
    }

    return rez;
}

string getLongestPolinom(vector<string> polinoms)
{
    string rez = polinoms[0];

    for (auto& p : polinoms)
    {
        if (p.length() > rez.length())
            rez = p;
    }

    return rez;
}

string getRes(string str)
{
    return (getLongestPolinom(getPolinoms(getWords(str))));
}

#include "conveyor.h"

string genWord(size_t size)
{
    string rez = string(size, '0');
    for (size_t i = 0; i < size; i++)
    {
        rez[i] = rand()%26 + 97;
    }
    return rez;
}

string genStr(size_t max_words_size, size_t words_number)
{
    string rez = "";
    for (size_t i = 0; i < words_number; i++)
    {
        rez += genWord(rand() % max_words_size + 1) + " ";
    }
    return rez;
}

int main()
{
    cout << "Hello World!" << endl;

    Conveyor c(103);
    vector<Request> requests = {Request("test lol 23323232 s sss ll 2332323322 sls sll lls"), Request("test lol 23323232 s sss ll 233232332 sls sll lls"), Request("te str")};
    for (int i = 0; i < 100; i++)
    {
        requests.push_back(genStr(3, 10));
    }
    //vector<Request> requests = {Request("test lol 23323232 s sss ll 2332323322 sls sll lls")};
    c.process(requests);


    return 0;
}
