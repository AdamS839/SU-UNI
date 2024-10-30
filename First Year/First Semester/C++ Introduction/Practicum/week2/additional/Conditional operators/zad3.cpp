#include <iostream>

int main() {
    float a, b, c;
    std::cin >> a >> b >> c;
    if ((a + b > c) && (a + c > b) && (b + c > a))
    {
        std::cout<< "Triangle can exist" << std::endl;
    }
    else std::cout << "Triangle cant exist" << std::endl;
    
}