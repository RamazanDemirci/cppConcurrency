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
What if i wana create many thread with fuure and promise?
in this point we talk about "shared_future"

#3 : unlike regular future, shared future can be copied.
#4 : function doesn't need to pass by reference of shared future

*/
/*#4*/
int factorial(std::shared_future<int> f)
{
    int res = 1;
    int N = f.get(); /*#6*/
    for (int i = N; i > 1; i--)
        res *= i;

    cout << "Result is: " << res << endl;
    return res;
}

int main()
{
    std::cout << "Hello Easy C++ project!" << std::endl;

    int x;

    std::promise<int> p;                    /*#1*/
    std::future<int> f = p.get_future();    /*#2*/
    std::shared_future<int> sf = f.share(); /*#3*/
    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(sf));
    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(sf));
    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(sf));
    //...10 thread

    p.set_value(4); /*#5*/

    return 0;
}