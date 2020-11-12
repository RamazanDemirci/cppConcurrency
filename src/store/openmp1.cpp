#include <iostream>
#include <stdio.h>

using namespace std;


int main() {
    #pragma omp parallel for
    for(int i = 0; i < 100; i++){
        printf("%i\n", i);
    }
    return 0;


    std::cout << "Hello Easy C++ project!" << std::endl;

   
    
}