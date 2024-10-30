#include <iostream>
#include <cmath>

int main() {
    double r, h;

    std:: cin >> r >> h;
    double S = 2 * M_PI * r * h + 2 * M_PI * r * r;
    double V = M_PI * r * r * h;
    std::cout<<"S = " << S << std::endl;
    std::cout<<"V = " << V << std::endl;  
}