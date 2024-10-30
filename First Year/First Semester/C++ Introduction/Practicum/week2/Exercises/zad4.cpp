#include <iostream>
#include <cmath>

int main() {
    double cylRadius, cylHeight, zRadius;

    std::cin >> cylRadius >> cylHeight >> zRadius;

    double cylV = M_PI * cylRadius * cylRadius * cylHeight;

    double zeleV = M_PI * pow(zRadius, 3) * 4 / 3;

    int zeleCount = floor((cylV / 2) / zeleV);

    std::cout<< "There can be " << zeleCount << " cabbages inside the canister." << std::endl;

}