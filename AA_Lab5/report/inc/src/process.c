void Conveyor::process(vector<Request> &requests)
{
    start_time = Clock::now();

    thread t1(&Conveyor::firstBent, this);
    thread t2(&Conveyor::secondBent, this);
    thread t3(&Conveyor::thirdBent, this);

    for (size_t i = 0; i < requests.size(); i++)
    {
        m1.lock();
        requests[i].push_time1 = duration_cast<nanoseconds>(Clock::now() - start_time).count()/1000000000.;
        queue1.push(requests[i]);
        m1.unlock();
    }

    t1.join();
    t2.join();
    t3.join();
}