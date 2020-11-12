#include <iostream>
#include <thread>

using namespace std;

void function_1(){
    std::cout << "Beaty is only skin-deep" << std::endl;
}

class Fctor {
public:
    void operator()(string &msg) {
        cout << "t1 says: " << msg << endl;
        msg = "Trust is the mother of deceit.";
    }
};

int main() {
    std::cout << "Hello Easy C++ project!" << std::endl;
    
    string s = "Where there is no trust, there is no love";
    std:thread t1((Fctor()), s); //"parameter to the thread always pass by the value"
    
    t1.join();

    cout << "from main: " << s << endl;
    return 0;
}