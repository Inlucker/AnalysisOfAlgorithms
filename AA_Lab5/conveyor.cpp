#include "conveyor.h"

Conveyor::Conveyor(int _n)
{
    n = _n;
}

void Conveyor::process(vector<Request> &requests)
{
    thread t1(&Conveyor::firstBent, this);
    thread t2(&Conveyor::secondBent, this);
    thread t3(&Conveyor::thirdBent, this);

    for (size_t i = 0; i < requests.size(); i++)
    {
        m1.lock();
        queue1.push(requests[i]);
        cout << "Pushed " << i+1 << " request into queue1" << endl;
        m1.unlock();
    }

    t1.join();
    t2.join();
    t3.join();
}


vector<string> Conveyor::getWords(string str)
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

vector<string> Conveyor::getPolinoms(vector<string> words)
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

string Conveyor::getLongestPolinom(vector<string> polinoms)
{
    if (polinoms.size() > 0)
    {
        string rez = polinoms[0];

        for (auto& p : polinoms)
        {
            if (p.length() > rez.length())
                rez = p;
        }

        return rez;
    }
    else
    {
        return "No polinoms";
    }
}

void Conveyor::firstBent()
{
    int cur_n = 0;
    while (true)
    {
        if (cur_n == n)
            break;
        m1.lock();
        if (queue1.empty())
        {
            m1.unlock();
            continue;
        }
        Request r = queue1.front();
        queue1.pop();
        cout << "Poped " << cur_n+1 << " request from queue1" << endl;
        m1.unlock();
        //r.words = getWords(r.str);
        r.getWords();
        m2.lock();
        queue2.push(r);
        cout << "Pushed " << cur_n+1 << " request into queue2" << endl;
        m2.unlock();
        cur_n ++;
    }
    cout << "bent1 is Done" << endl;
}

void Conveyor::secondBent()
{
    int cur_n = 0;
    while (true)
    {
        if (cur_n == n)
            break;
        m2.lock();
        if (queue2.empty())
        {
            m2.unlock();
            continue;
        }
        Request r = queue2.front();
        queue2.pop();
        cout << "Poped " << cur_n+1 << " request from queue2" << endl;
        m2.unlock();
        //r.polinoms = getPolinoms(r.words);
        r.getPolinoms();
        m3.lock();
        queue3.push(r);
        cout << "Pushed " << cur_n+1 << " request into queue3" << endl;
        m3.unlock();
        cur_n ++;
    }
    cout << "bent2 is Done" << endl;
}

void Conveyor::thirdBent()
{
    int cur_n = 0;
    while (true)
    {
        if (cur_n == n)
            break;
        m3.lock();
        if (queue3.empty())
        {
            m3.unlock();
            continue;
        }
        Request r = queue3.front();
        queue3.pop();
        cout << "Poped " << cur_n+1 << " request from queue3" << endl;
        m3.unlock();
        //r.longest_polinom = getLongestPolinom(r.polinoms);
        r.getLongestPolinom();

        cout << r.str << endl;
        for (auto& w : r.words)
            cout << w << "; ";
        cout << endl;
        for (auto& p : r.polinoms)
            cout << p << "; ";
        cout << endl;
        cout << r.longest_polinom << endl;

        cur_n ++;

    }
    cout << "bent3 is Done" << endl;
}
