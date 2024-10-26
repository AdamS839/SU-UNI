#include <iostream>
#include <algorithm>

int main() {
    float a, b, tempVariable;
    std::cin >> a >> b;

    tempVariable = a;
    a = b;
    b = tempVariable;
    
    /*
    a = a + b;
    b = a - b;
    a = a - b;
    */


    //std::swap(a, b);

    std::cout << "The value of A is: " << a <<std::endl;
    std::cout << "The value of B is: " << b << std::endl;
}