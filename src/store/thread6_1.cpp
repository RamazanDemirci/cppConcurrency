#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>
#include <deque>
#include <chrono>

using namespace std;

std::deque<int> q;
std::mutex mu;

/*
#1 : this code always check queue is empty and lock and unlock mutex. we dont wanna this wasting.
*/

void function_1()
{
    int count = 10;
    while (count > 0)
    {
        std::unique_lock<mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
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
        if (!q.empty())
        { /*#1*/
            data = q.back();
            q.pop_back();
            locker.unlock();
            cout << "t2 got a value from t1" << data << endl;
        }
        else
        {
            locker.unlock();
        }
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