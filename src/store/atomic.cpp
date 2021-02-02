
#include <iostream>
#include <atomic>
#include <thread>

int main()
{
    std::atomic<int> x;
    x = 5;

    std::thread t1([&]() {
        for (int i = 0; i < 1000; i++)
            std::cout << "inc " << ++x << std::endl;
    });

    std::thread t2([&]() {
        for (int i = 0; i < 1000; i++)
            std::cout << "dec " << --x << std::endl;
    });

    t1.join();
    t2.join();

    std::cout << "deneme" << std::endl;
}