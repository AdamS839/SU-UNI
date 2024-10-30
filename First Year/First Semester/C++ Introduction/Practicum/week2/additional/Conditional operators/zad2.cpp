#include <iostream>
#include <algorithm>
#include <cmath>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;

    // 10 20 30

    int maxFromAB = ((a + b + abs(a - b)) / 2);
    int max = (maxFromAB + c + abs(maxFromAB- c)) / 2;
    // 10 + 20 + 10 = 40 / 2 = 20 biggest from a and b
    // 20 + 30 + 10 = 60 / 2 = 30 biggest from a and b and c

    int minFromAB = (a + b - abs(a - b)) / 2;
    int min = (minFromAB + c - abs(minFromAB - c)) / 2;
    // same for minimum

    std::cout<< "Biggest number is: " << max << std::endl;
    std::cout<< "Smallest number is: " << min << std::endl;


    //std::cout << "Biggest number is: " << std::max(std::max(a, b), c) << std::endl;
    //std::cout << "Smallest number is: " << std::min(std::min(a, b), c) << std::endl;
}