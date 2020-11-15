#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>

using namespace std;

//#1 : Lazy Initialization(Initialization Upon First Use Idiom)
/*#2 : Why use another unique lock? 
        - file open only once. but print process many times. 
        and we dont wanna use the same locker for difference purpose.
  #3 : this is thread safe but we lock and unlokc mutext every print operation. 
    this wasting the computer cycles. and we dont wanna spend computing performance to waste
*/

class LogFile
{
    std::mutex _mu;
    std::mutex _mu_open;
    ofstream _f;

public:
    LogFile()
    {
    } // Need destructor to close file
    void shared_print(string id, int value)
    {
        {                                              /*#3*/
            std::unique_lock<mutex> locker2(_mu_open); /*#2*/
            if (!_f.is_open())
            { /*#1*/
                _f.open("log.txt");
            }
        }

        std::unique_lock<mutex> locker(_mu, std::defer_lock);
        cout << "From " << id << ": " << value << endl;
    }
};

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