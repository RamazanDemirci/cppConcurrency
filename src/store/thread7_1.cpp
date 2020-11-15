#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

using namespace std;

/*
#1 : this variable shared between threads. and we need to protect this.
*/

void factorial(int N, int &x)
{
    int res = 1;
    for (int i = N; i > 1; i--)
    {
        res *= i;
    }
    cout << "Result is: " << res << endl;
    x = res;
}

int main()
{
    int x; /*#1*/
    std::cout << "Hello Easy C++ project!" << std::endl;

    std::thread t1(factorial, 4, std::ref(x));
    t1.join();
    return 0;
}