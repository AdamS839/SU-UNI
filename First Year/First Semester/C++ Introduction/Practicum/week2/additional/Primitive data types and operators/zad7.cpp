#include <iostream>

int main() {
    float a = 0.2;
    float b = 0.1;
    float const e = 0.00001;
    if ((a+b - 0.3) < e) {
        std::cout << "computers can do simple math, of course!";
    }
}