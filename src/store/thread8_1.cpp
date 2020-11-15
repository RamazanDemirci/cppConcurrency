#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

using namespace std;

std::mutex mu;
std::condition_variable cond;

/*Using Callable Objects

#1 : copy of 'a' which is callable object,
    invoked as a Functor in different thread
#2 : launch as a functor in different thread
#3 : create temporary 'A'; temporary A is moved into the thread object and then create a thread.

ps : this callable object does not have to be functor. 

#4.: it can be regular function. 
#5 : it can also be a lambda function. 
#6 :it can also be a class member function.
    copy of 'a' invoke 'f' function in different thread
#7 : pass by reference of 'a' invoke 'f' function in different thread
#8 : a is no longer usable in main thread(or parent thread)

*/

class A
{
public:
    void f(int x, char c) {}
    long g(double x) { return 0; }
    int operator()(int N) { return 0; }
};

int foo(int x)
{
}

int main()
{
    A a;
    std::thread t1(a, 6);                           /*#1*/
    std::thread t2(std::ref(a), 6);                 /*#2*/
    std::thread t8(std::ref(a), 6);                 /*#8*/
    std::thread t3(A(), 6);                         /*#3*/
    std::thread t4([](int x) { return x * x; }, 6); /*#4*/
    std::thread t5(foo, 7);                         /*#5*/
    std::thread t6(&A::f, a, 8, 'w');               /*#6*/
    std::thread t7(&A::f, &a, 8, 'w');              /*#7*/
    return 0;
}