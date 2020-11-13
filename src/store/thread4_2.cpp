#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>

using namespace std;

class LogFile
{
    std::mutex _mu;
    std::mutex _mu2;
    ofstream f;

public:
    LogFile()
    {
        f.open("log.txt");
    } // Need destructor to close file
    void shared_print(string id, int value)
    {
        std::lock(_mu, _mu2);
        std::lock_guard<mutex> locker(_mu, std::adopt_lock);
        std::lock_guard<mutex> locker2(_mu2, std::adopt_lock);
        cout << "From " << id << ": " << value << endl;
    }
    void shared_print2(string id, int value)
    {
        std::lock_guard<mutex> locker(_mu);
        std::lock_guard<mutex> locker2(_mu2);

        cout << "From " << id << ": " << value << endl;
    }
};

/* Avoiding deadlock 
1. Prefer locking single mutex.
2. Avoid locking a mutex and then calling a user provided function.
3. Use std::lock() to lock more than one mutex.
4. Lock the mutex in same order.

Locking Granularity:
- Fine-grained lock: protects smal amount of data
- Coarse-grained lock: protects big amount of data
*/

void function_1(LogFile &log)
{
    for (int i = 0; i > -100; i--)
    {
        log.shared_print(string("t1: "), i);
    }
}

int main()
{
    std::cout << "Hello Easy C++ project!" << std::endl;

    LogFile log;
    std::thread t1(function_1, std::ref(log));

    for (int i = 0; i < 100; i++)
    {
        log.shared_print2(string("From main: "), i);
    }

    t1.join();
    return 0;
}