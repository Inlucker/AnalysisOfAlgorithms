#include "conveyor.h"

//using namespace std;
//using namespace chrono;

//#include "tools.h"


Conveyor::Conveyor(int _n)
{
    n = _n;
}

void Conveyor::process(vector<Request> &requests)
{
    //start_time = clock();

    start_time = Clock::now();
    //Sleep(1000);

    //cout << "Start time: " << double(start_time) / CLOCKS_PER_SEC << endl;

    thread t1(&Conveyor::firstBent, this);
    thread t2(&Conveyor::secondBent, this);
    thread t3(&Conveyor::thirdBent, this);

    for (size_t i = 0; i < requests.size(); i++)
    {
        //m1.lock();
        requests[i].push_time1 = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;
        queue1.push(requests[i]);
        //cout << "Pushed " << i+1 << " request into queue1" << endl;
        //m1.unlock();
    }

    t1.join();
    t2.join();
    t3.join();
}

vector<Request> Conveyor::getRes()
{
    return res;
}

/*clock_t Conveyor::process(vector<string> objvec)
{
    timer.set_size(n);

    start_t = clock();

    thread t1(&Conveyor::first_conv, this);
    thread t2(&Conveyor::second_conv, this);
    thread t3(&Conveyor::third_conv, this);

    for (int i = 0; i < n; i++) {
        m1.lock();
        queue1.push(Request(objvec[i], i, clock()));
        m1.unlock();
    }

    t1.join();
    t2.join();
    t3.join();

    return start_t;
}*/


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
        r.pop_time1 = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;
        //cout << "Poped " << cur_n+1 << " request from queue1" << endl;
        m1.unlock();
        //r.words = getWords(r.str);
        r.getWords();
        m2.lock();
        r.push_time2 = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;
        queue2.push(r);
        //cout << "Pushed " << cur_n+1 << " request into queue2" << endl;
        m2.unlock();
        cur_n ++;
    }
    //cout << "bent1 is Done" << endl;
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
        r.pop_time2 = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;
        //cout << "Poped " << cur_n+1 << " request from queue2" << endl;
        m2.unlock();
        //r.polinoms = getPolinoms(r.words);
        r.getPolinoms();
        m3.lock();
        r.push_time3 = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;
        queue3.push(r);
        //cout << "Pushed " << cur_n+1 << " request into queue3" << endl;
        m3.unlock();
        cur_n ++;
    }
    //cout << "bent2 is Done" << endl;
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
        r.pop_time3 = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;
        //cout << "Poped " << cur_n+1 << " request from queue3" << endl;
        m3.unlock();
        //r.longest_polinom = getLongestPolinom(r.polinoms);
        r.getLongestPolinom();
        r.processing_time = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;
        //cout << "Done " << cur_n+1 << " request" << endl;

        //debug print
        /*cout << r.str << endl;
        for (auto& w : r.words)
            cout << w << "; ";
        cout << endl;
        for (auto& p : r.polinoms)
            cout << p << "; ";
        cout << endl;
        cout << r.longest_polinom << endl;*/

        /*cout << "Request #" << cur_n+1 << ":" << endl;
        cout << "push_time1: " << r.push_time1 << " s" << endl;
        cout << "pop_time1:  "<< r.pop_time1 << " s" << endl;
        cout << "push_time2: " << r.push_time2 << " s" << endl;
        cout << "pop_time2:  "<< r.pop_time2 << " s" << endl;
        cout << "push_time3: " << r.push_time3 << " s" << endl;
        cout << "pop_time3:  "<< r.pop_time3 << " s" << endl;
        cout << "proc_time:  "<< r.processing_time << " s" << endl;
        cout << endl;*/

        m4.lock();
        res.push_back(r);
        m4.unlock();
        cur_n ++;

    }
    //cout << "bent3 is Done" << endl;
}

/*void Conveyor::first_conv()
{
    int num = 0;
    while (true)
    {
        if (num == n)
            break;
        m1.lock();
        if (queue1.empty())
        {
            m1.unlock();
            continue;
        }
        Request cur_obj = queue1.front();
        timer.add_time_from_start(queue1.front().time, cur_obj.task_num);
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(1, clock() - queue1.front().time, queue1.front().task_num);
        queue1.pop();

        clock_t cur_time = clock();
        m1.unlock();
        cur_obj.getWords();
        m2.lock();
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(0, clock() - cur_time, cur_obj.task_num);

        queue2.push(cur_obj);
        m2.unlock();
        num++;
    }
}

void Conveyor::second_conv()
{
    int num = 0;
    while (true)
    {
        if (num == n)
            break;
        m2.lock(); // wait in queue
        if (queue2.empty())
        {
            m2.unlock();
            continue;
        }
        Request cur_obj = queue2.front();
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(1, clock() - queue2.front().time, queue2.front().task_num);
        queue2.pop();

        clock_t cur_time = clock();
        m2.unlock();
        cur_obj.getPolinoms();
        m3.lock();
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(0, clock() - cur_time, cur_obj.task_num);

        queue3.push(cur_obj);
        m3.unlock();
        num++;
    }
}

void Conveyor::third_conv()
{
    int num = 0;
    while (true)
    {
        if (num == n)
            break;
        m3.lock(); // wait in queue
        if (queue3.empty())
        {
            m3.unlock();
            continue;
        }
        Request cur_obj = queue3.front();
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(1, clock() - queue3.front().time, queue3.front().task_num);
        queue3.pop();

        clock_t cur_time = clock();
        m3.unlock();
        cur_obj.getLongestPolinom();
        resm.lock();
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(0, clock() - cur_time, cur_obj.task_num);

        res.push_back(cur_obj);
        resm.unlock();
        num++;
    }
}*/
