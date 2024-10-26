#include <iostream>
#include <cmath>

int main() {
    float x1, y1, x2, y2;
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;

    std::cout<<"The distance between the two points is: " << sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) << std::endl;
}