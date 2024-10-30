#include <iostream>
#include <cmath>

int main() {
    int curr, prev;
    int biggestDiff = 0;

    do
    {
        std::cin >> curr;
        if (curr < 0) continue;
        int diff = curr - prev;
        if (biggestDiff < diff) biggestDiff = diff;
        prev = curr;
    } while (curr != 0);
    std::cout<< biggestDiff << std::endl;
}