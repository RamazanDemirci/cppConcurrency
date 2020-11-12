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
        msg = "Trust is the mother of deceit.";
    }
};

int main() {
    std::cout << "Hello Easy C++ project!" << std::endl;
    
    string s = "Where there is no trust, there is no love";
    cout << std::this_thread::get_id() << endl;

    std:thread t1((Fctor()), std::move(s)); 
    cout << t1.get_id() << endl;

    std::thread t2 = std::move(t1);

    t2.join();

    cout << "from main: " << s << endl; //std::move ile geçirdiğimizde main thread tarafından bu değişken print edilemiyor 
    return 0;
}