#include <iostream>
#include <cmath>

float Surface(float radius){
    return radius <= 0 ? 0 : M_PI * radius * radius;
}

int main() {
    std::cout << Surface(4) << std::endl;
}