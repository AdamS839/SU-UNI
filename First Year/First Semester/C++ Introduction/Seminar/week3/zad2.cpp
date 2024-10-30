#include <iostream>
#include <cmath>

int main() {
    int n;
    int max = 0;

    do
    {
        std::cin >> n;
        if (n < 0)
        {
            continue;
        }
        if (n > max) max = n;
    } while (n != 0);
    std::cout<< max << std::endl;
}