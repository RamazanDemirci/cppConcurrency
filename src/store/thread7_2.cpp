#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

using namespace std;

std::mutex mu;
std::condition_variable cond;

/*
#1 : this wait child thread finish and then return the value from the child thread.
    future ; represent an object where you can get smt in the future
#2 : fu.get(); called only once.
    if we try to call again fu.get program will be crash.
#3 : std::async func. may ot may  not create another thread, that can be controlled by another parameter
#4 : std::launch::deferred is a parameter which control async func create or not create new thread. 
    if this parameter pass to the async function new thread not created. 
    execution of the function which passed to the "async", defer to time when fu.get() called.
#5 : std::launch::async is a parameter which cause create another thread.
#6 : std::launch::deferred | std::launch::async this is default value of std::async
*/

int factorial(int N)
{
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;

    cout << "Result is: " << res << endl;
    return res;
}

int main()
{
    std::cout << "Hello Easy C++ project!" << std::endl;

    int x;
    //std::future<int> fu = std::async(factorial, 4);                        /*#3*/
    //std::future<int> fu = std::async(std::launch::deferred, factorial, 4); /*#4*/
    std::future<int> fu = std::async(std::launch::async, factorial, 4); /*#5*/
    x = fu.get();                                                       /*#1*/
    //fu.get()/*#2*/
    return 0;
}