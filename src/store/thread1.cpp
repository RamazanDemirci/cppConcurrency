#include <iostream>
#include <thread>

using namespace std;

void function_1()
{
    std::cout << "Beaty is only skin-deep" << std::endl;
}

int main()
{
    std::cout << "Hello Easy C++ project!" << std::endl;

std:
    thread t1(function_1);
    //t1.join(); //main thread waits for t1 to finish
    t1.detach(); //t1 will freely on its own -- daemon process
    //The detached thread cannot be joined back once detached

    //..

    if (t1.joinable())
    {
        std::cout << "joinable" << std::endl;
        t1.join();
    }
    return 0;
}