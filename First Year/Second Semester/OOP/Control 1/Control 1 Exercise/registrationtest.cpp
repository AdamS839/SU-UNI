#include "Registration.h"

int main(){
    Registration r1{"XX1111XX"};
    Registration r2{"AB1234AB"};

    std::cout << r1.toString() << std::endl;
    std::cout << std::boolalpha << (r1 == r2) << std::endl;

    return 0;
}