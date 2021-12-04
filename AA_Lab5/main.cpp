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

#define N 100

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
