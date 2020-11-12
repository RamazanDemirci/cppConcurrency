#include <iostream>
#include <thread>

using namespace std;

void function_1(){
    std::cout << "Beaty is only skin-deep" << std::endl;
}

class Fctor {
public:
    void operator()(string msg) {
        cout << "t1 says: " << msg << endl;
    }
};

int main() {
    std::cout << "Hello Easy C++ project!" << std::endl;
    
    string s = "Where there is no trust, there is no love";
    std:thread t1((Fctor()), s); //works
    
    try{
       cout << "from main: " << s << endl;
    }
    catch(...){
        t1.join();
        throw;

    }
    t1.join();
    return 0;
}