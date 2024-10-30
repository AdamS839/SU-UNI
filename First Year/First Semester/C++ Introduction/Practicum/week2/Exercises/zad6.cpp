#include <iostream>

int main() {
    int a, b, c;

    std::cin >> a >> b >> c;

    if ((a + b > c) && (a + c > b) && (c + b > a))
    {
        std::cout<< "Triangle exists" << std::endl;
    }
    else std::cout << "Triangle doesnt exist" << std::endl;
    
}