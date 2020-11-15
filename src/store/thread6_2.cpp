#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>
#include <deque>
#include <chrono>
#include <condition_variable>

using namespace std;

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

/*
#1 : Notify one waiting thread, if there is one.
#2 : Wait for other thread notify.
    that is called "spurious wake"
#3 : we can add pridicate parameter. in this line; if queue is empty thread going to sleep again. 
#4 : this is performed to send notify all other threads. 
*/

void function_1()
{
    int count = 10;
    while (count > 0)
    {
        std::unique_lock<mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        cond.notify_one(); /*#1*/
        cond.notify_all(); /*#4*/
        std::this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}

void function_2()
{
    int data = 0;
    while (data != 1)
    {
        std::unique_lock<mutex> locker(mu);
        //cond.wait(locker); /*#2*/
        cond.wait(locker, []() { return !q.empty(); }); /*#3*/
        data = q.back();
        q.pop_back();
        locker.unlock();
        cout << "t2 got a value from t1" << data << endl;
    }
}

int main()
{
    std::cout << "Hello Easy C++ project!" << std::endl;

    std::thread t1(function_1);
    std::thread t2(function_2);
    t1.join();
    t2.join();
    return 0;
}