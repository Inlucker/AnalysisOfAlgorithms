#include <iostream>
#include <string.h>
#include <vector>
#include <random>
#include <ctime>

//#include "windows.h"

#include "conveyor.h"
//#include "tools.h"

using namespace std;

using namespace chrono;

vector<string> getWords(string str)
{
    Sleep(1);
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
    Sleep(1);
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
    Sleep(1);
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

string getRes(string str)
{
    return (getLongestPolinom(getPolinoms(getWords(str))));
}


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

#define N 10

int main()
{
    srand(time(0));
    cout << "Hello World!" << endl;

    vector<Request> requests;// = {Request("test lol 23323232 s sss ll 2332323322 sls sll lls"), Request("test lol 23323232 s sss ll 233232332 sls sll lls"), Request("te str")};
    for (int i = 0; i < N; i++)
    {
        requests.push_back(genStr(3, 10000));
    }
    //vector<Request> requests = {Request("test lol 23323232 s sss ll 2332323322 sls sll lls")};

    Conveyor c(requests.size());

    time_point<high_resolution_clock> start = Clock::now();
    //double start = getCPUTime();
    c.process(requests);
    //double end = getCPUTime();
    //cout << "Conveyor time: " << end - start << " s" << endl;
    time_point<high_resolution_clock> end = Clock::now();
    nanoseconds diff = duration_cast<nanoseconds>(end - start);
    cout << "Conveyor time:" << endl;
    cout << diff.count() << " ns\n";
    cout << diff.count() / 1000000. << " ms\n";
    cout << diff.count() / 1000000000. << " s\n";
    cout << endl;

    vector<Request> res = c.getRes();

    res[0].calculateTimes();
    double min_queue_time = res[0].queue_time1;
    double max_queue_time = res[0].queue_time1;
    double avg_queue_time = 0;
    int times_n = 0;

    double min_proc_time = res[0].own_proc_time;
    double max_proc_time = res[0].own_proc_time;
    double avg_proc_time = 0;
    int times_n2 = 0;

    printf("|Reqest # | push_time1 |  pop_time1 | push_time2 |  pop_time2 | push_time3 |  pop_time3 |  proc_time |\n");
    printf("|---------|------------|------------|------------|------------|------------|------------|------------|\n");
    for (size_t i = 0; i < res.size(); i++)
    {
        res[i].calculateTimes();
        printf("|%8d | %10f | %10f | %10f | %10f | %10f | %10f | %10f |\n",
               i+1, res[i].push_time1, res[i].pop_time1, res[i].push_time2, res[i].pop_time2, res[i].push_time3, res[i].pop_time3, res[i].processing_time);
        //min
        if (res[i].queue_time1 < min_queue_time)
            min_queue_time = res[i].queue_time1;
        if (res[i].queue_time2 < min_queue_time)
            min_queue_time = res[i].queue_time2;
        if (res[i].queue_time3 < min_queue_time)
            min_queue_time = res[i].queue_time3;

        if (res[i].own_proc_time < min_proc_time)
            min_proc_time = res[i].own_proc_time;
        //max
        if (res[i].queue_time1 > max_queue_time)
            max_queue_time = res[i].queue_time1;
        if (res[i].queue_time2 > max_queue_time)
            max_queue_time = res[i].queue_time2;
        if (res[i].queue_time3 > max_queue_time)
            max_queue_time = res[i].queue_time3;

        if (res[i].own_proc_time > max_proc_time)
            max_proc_time = res[i].own_proc_time;
        //avg
        avg_queue_time += res[i].queue_time1 + res[i].queue_time2 + res[i].queue_time3;
        times_n += 3;

        avg_proc_time += res[i].own_proc_time;
        times_n2 ++;
        //cout << res[i].own_proc_time << endl;
    }
    avg_queue_time /= times_n;
    avg_proc_time /= times_n2;
    printf("|---------|------------|------------|------------|------------|------------|------------|------------|\n");

    cout << endl;
    cout << "min_queue_time = " << min_queue_time << endl;
    cout << "max_queue_time = " << max_queue_time << endl;
    cout << "avg_queue_time = " << avg_queue_time << endl;
    cout << "min_proc_time =  " << min_proc_time << endl;
    cout << "max_proc_time =  " << max_proc_time << endl;
    cout << "avg_proc_time =  " << avg_proc_time << endl;
    cout << endl;

    start = Clock::now();
    //start = getCPUTime();
    //for (int i = 0; i < N; i++)
        //string tmp_res = getRes(requests[i].str);
    //int i = 1;
    for (auto& r : requests)
    {
        //cout << "Request #" << i++ << ":" << endl;
        //cout << "startTime: " << duration_cast<nanoseconds>(Clock::now() - start).count()/1000000000. << " s" << endl;
        r.getWords();
        //cout << "getWords: " << duration_cast<nanoseconds>(Clock::now() - start).count()/1000000000. << " s" << endl;
        r.getPolinoms();
        //cout << "getPolinoms:  "<< duration_cast<nanoseconds>(Clock::now() - start).count()/1000000000. << " s" << endl;
        r.getLongestPolinom();
        //cout << "getLongestPolinom: " << duration_cast<nanoseconds>(Clock::now() - start).count()/1000000000. << " s" << endl;
        //cout << endl;
        /*vector<string> tmp_words = getWords(r.str);
        vector<string> tmp_polinoms = getPolinoms(tmp_words);
        string longest_polinom = getLongestPolinom(tmp_polinoms);*/
        //string tmp_res = getRes(r.str);
    }
    //end = getCPUTime();
    //cout << "Without conveyor time: " << end - start << " s" << endl;
    end = Clock::now();
    diff = duration_cast<nanoseconds>(end - start);
    cout << "Without conveyor time:" << endl;
    cout << diff.count() << " ns\n";
    cout << diff.count() / 1000000. << " ms\n";
    cout << diff.count() / 1000000000. << " s\n";
    cout << endl;

    //ADDED
    /*vector<Request> res;
    vector<string> objvec;
    objvec.resize(N);

    for (int i = 0; i < N; i++)
    {
        string s = genStr(300, 1000);
        objvec[i] = (s);
    }

    Conveyor conv(objvec.size());

    clock_t start_t = conv.process(objvec);
    clock_t time1 = clock() - start_t;

    start_t = clock();

    for (int i = 0; i < N; i++)
    {
        Request cur_obj = Request(objvec[i], i, clock());
        cur_obj.getWords();
        cur_obj.getPolinoms();
        cur_obj.getLongestPolinom();
        res.push_back(cur_obj);
    }

    clock_t time2 = clock() - start_t;

    fprintf(stdout, "Time with conveyor: %lf\n", (double) time1 / CLOCKS_PER_SEC);
    fprintf(stdout, "Time without conveyor: %lf\n", (double) time2 / CLOCKS_PER_SEC);*/

    return 0;
}
