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
        m1.unlock();
        r.getWords();
        m2.lock();
        r.push_time2 = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;
        queue2.push(r);
        m2.unlock();
        cur_n ++;
    }
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
        m2.unlock();
        r.getPolinoms();
        m3.lock();
        r.push_time3 = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;
        queue3.push(r);
        m3.unlock();
        cur_n ++;
    }
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
        m3.unlock();
        r.getLongestPolinom();
        r.processing_time = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;

        m4.lock();
        res.push_back(r);
        m4.unlock();
        cur_n ++;

    }
}