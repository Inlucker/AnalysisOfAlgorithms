#include <iostream>
#include <string.h>
#include <vector>
#include <random>
#include <ctime>

//#include "windows.h"

#include "conveyor.h"
//#include "tools.h"

//using namespace std;
//using namespace chrono;

typedef std::chrono::high_resolution_clock Clock;

std::vector<std::string> getWords(std::string str)
{
    Sleep(1);
    std::vector<std::string> rez;

    std::string tmp = "";
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

std::vector<std::string> getPolinoms(std::vector<std::string> words)
{
    Sleep(1);
    std::vector<std::string> rez;

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

std::string getLongestPolinom(std::vector<std::string> polinoms)
{
    Sleep(1);
    if (polinoms.size() > 0)
    {
        std::string rez = polinoms[0];

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

std::string getRes(std::string str)
{
    return (getLongestPolinom(getPolinoms(getWords(str))));
}


std::string genWord(size_t size)
{
    std::string rez = std::string(size, '0');
    for (size_t i = 0; i < size; i++)
    {
        rez[i] = rand()%26 + 97;
    }
    return rez;
}

std::string genStr(size_t max_words_size, size_t words_number)
{
    std::string rez = "";
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
    //std::cout << "Hello World!" << std::endl;

    std::vector<Request> requests;// = {Request("test lol 23323232 s sss ll 2332323322 sls sll lls"), Request("test lol 23323232 s sss ll 233232332 sls sll lls"), Request("te str")};
    for (int i = 0; i < N; i++)
    {
        requests.push_back(genStr(10, 10000));
    }
    //std::vector<Request> requests = {Request("test lol 23323232 s sss ll 2332323322 sls sll lls")};

    Conveyor c(requests.size());

    std::chrono::time_point<Clock> start = Clock::now();
    //double start = getCPUTime();
    c.process(requests);
    //double end = getCPUTime();
    //std::cout << "Conveyor time: " << end - start << " s" << std::endl;
    std::chrono::time_point<Clock> end = Clock::now();
    std::chrono::nanoseconds diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Conveyor time:" << std::endl;
    std::cout << diff.count() << " ns\n";
    std::cout << diff.count() / 1000000. << " ms\n";
    std::cout << diff.count() / 1000000000. << " s\n";
    std::cout << std::endl;

    std::vector<Request> res = c.getRes();

    res[0].calculateTimes();
    double min_queue_time = res[0].queue_time1;
    double max_queue_time = res[0].queue_time1;
    double avg_queue_time = 0;
    int times_n = 0;

    double min_proc_time = res[0].own_proc_time;
    double max_proc_time = res[0].own_proc_time;
    double avg_proc_time = 0;
    int times_n2 = 0;

    double avg_proc1_time = 0;
    double avg_proc2_time = 0;
    double avg_proc3_time = 0;

    double avg_queue1_time = 0;
    double avg_queue2_time = 0;
    double avg_queue3_time = 0;

    printf("|Reqest # | push_time1 |  pop_time1 | push_time2 |  pop_time2 | push_time3 |  pop_time3 |  proc_time |\n");
    printf("|---------|------------|------------|------------|------------|------------|------------|------------|\n");
    for (size_t i = 0; i < res.size(); i++)
    {
        res[i].calculateTimes();
        printf("|%8lld | %10f | %10f | %10f | %10f | %10f | %10f | %10f |\n",
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

        avg_proc1_time += res[i].push_time2 - res[i].pop_time1;
        avg_proc2_time += res[i].push_time3 - res[i].pop_time2;
        avg_proc3_time += res[i].processing_time - res[i].pop_time3;

        avg_queue1_time += res[i].queue_time1;
        avg_queue2_time += res[i].queue_time2;
        avg_queue3_time += res[i].queue_time3;

        //std::cout << res[i].own_proc_time << std::endl;
    }
    avg_queue_time /= times_n;
    avg_proc_time /= times_n2;
    avg_proc1_time /= times_n2;
    avg_proc2_time /= times_n2;
    avg_proc3_time /= times_n2;
    avg_queue1_time /= times_n2;
    avg_queue2_time /= times_n2;
    avg_queue3_time /= times_n2;
    printf("|---------|------------|------------|------------|------------|------------|------------|------------|\n");

    std::cout << std::endl;
    std::cout << "min_queue_time = " << min_queue_time << std::endl;
    std::cout << "max_queue_time = " << max_queue_time << std::endl;
    std::cout << "avg_queue_time = " << avg_queue_time << std::endl;
    std::cout << std::endl;
    std::cout << "min_proc_time =  " << min_proc_time << std::endl;
    std::cout << "max_proc_time =  " << max_proc_time << std::endl;
    std::cout << "avg_proc_time =  " << avg_proc_time << std::endl;
    std::cout << std::endl;
    std::cout << "avg_proc1_time =  " << avg_proc1_time << std::endl;
    std::cout << "avg_proc2_time =  " << avg_proc2_time << std::endl;
    std::cout << "avg_proc3_time =  " << avg_proc3_time << std::endl;
    std::cout << std::endl;
    std::cout << "avg_queue1_time =  " << avg_queue1_time << std::endl;
    std::cout << "avg_queue2_time =  " << avg_queue2_time << std::endl;
    std::cout << "avg_queue3_time =  " << avg_queue3_time << std::endl;
    std::cout << std::endl;

    start = Clock::now();
    //start = getCPUTime();
    //for (int i = 0; i < N; i++)
        //std::string tmp_res = getRes(requests[i].str);
    //int i = 1;
    for (auto& r : requests)
    {
        //std::cout << "Request #" << i++ << ":" << std::endl;
        //std::cout << "startTime: " << std::chrono::duration_cast<nanoseconds>(Clock::now() - start).count()/1000000000. << " s" << std::endl;
        r.getWords();
        //std::cout << "getWords: " << std::chrono::duration_cast<nanoseconds>(Clock::now() - start).count()/1000000000. << " s" << std::endl;
        r.getPolinoms();
        //std::cout << "getPolinoms:  "<< std::chrono::duration_cast<nanoseconds>(Clock::now() - start).count()/1000000000. << " s" << std::endl;
        r.getLongestPolinom();
        //std::cout << "getLongestPolinom: " << std::chrono::duration_cast<nanoseconds>(Clock::now() - start).count()/1000000000. << " s" << std::endl;
        //std::cout << std::endl;
        /*std::vector<std::string> tmp_words = getWords(r.str);
        std::vector<std::string> tmp_polinoms = getPolinoms(tmp_words);
        std::string longest_polinom = getLongestPolinom(tmp_polinoms);*/
        //std::string tmp_res = getRes(r.str);
    }
    //end = getCPUTime();
    //std::cout << "Without conveyor time: " << end - start << " s" << std::endl;
    end = Clock::now();
    diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Without conveyor time:" << std::endl;
    std::cout << diff.count() << " ns\n";
    std::cout << diff.count() / 1000000. << " ms\n";
    std::cout << diff.count() / 1000000000. << " s\n";
    std::cout << std::endl;

    //ADDED
    /*std::vector<Request> res;
    std::vector<std::string> objvec;
    objvec.resize(N);

    for (int i = 0; i < N; i++)
    {
        std::string s = genStr(300, 1000);
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
