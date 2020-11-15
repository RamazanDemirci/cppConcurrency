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
#1 : we create a promise variable. this variable initialize in the futur. we promise that to the program.
#2 : we acquaint(introduce) this promise variable to the future variable. 
#3 : we pass by reference future variable to the thread. now thread aware of that in the future a variable coming to thread.
#4 : programdoing smt else. any time passed.
#5 : this line we initialize the promise variable.(in the future). and fu.get() line execute the thread according to this promise variable value.
*/

int factorial(std::future<int> &f)
{
    int res = 1;
    int N = f.get();
    for (int i = N; i > 1; i--)
        res *= i;

    cout << "Result is: " << res << endl;
    return res;
}

int main()
{
    std::cout << "Hello Easy C++ project!" << std::endl;

    int x;

    std::promise<int> p;                                                          /*#1*/
    std::future<int> f = p.get_future();                                          /*#2*/
    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f)); /*#3*/

    //doing smt
    std::this_thread::sleep_for(chrono::milliseconds(20)); /*#4*/
    p.set_value(4);                                        /*#5*/
    x = fu.get();
    cout << "Get from child: " << x << endl;
    return 0;
}