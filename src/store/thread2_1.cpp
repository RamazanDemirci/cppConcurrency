#include <iostream>
#include <thread>

using namespace std;

void function_1(){
    std::cout << "Beaty is only skin-deep" << std::endl;
}

class Fctor {
public:
    void operator()() {
        for(int i = 0; i > -100; i--){
            cout << "from t1" << i << endl;
        }
    }
};


int main() {
    std::cout << "Hello Easy C++ project!" << std::endl;

    //Fctor fct;
    //std:thread t1(fct); //works
    //std:thread t1(Fctor()); //compile error
    std:thread t1((Fctor())); //works
    
    // using RAII
    // Wrapper w(t1)
    
    try{
        for(int i = 0;  i < 100; i++){
            cout << "from main: " << i << endl;
        }
    }
    catch(...){
        t1.join();
        throw;

    }
    t1.join();
    return 0;
}