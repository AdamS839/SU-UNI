#include <iostream>
#include <cmath>


int digitCount(int n){
    if (n == 0) return 1;
    int result = 0;

    while (n != 0)
    {
        n /= 10;
        ++result;
    }

    return result;
}

int ReversedDigit(int n){
    if (n == 0) return 0;
    while (n != 0)
    {
        int reverseddigit = n % 10;
        std::cout<< reverseddigit << " ";
        n = n / 10;
    }
}


int main() {
    int n;
    int reverseddigit;
    int digitCount = 0;


    std::cout << digitCount << std::endl;
    ReversedDigit(n);
    /*
    do
    {
        std::cin>> n;
    } while (n < 0);

    
    while (n != 0)
    {
        reverseddigit = n % 10;
        std::cout<< reverseddigit << " ";
        n = n / 10;
    }
    if (n == 0)
    {
        reverseddigit = 0;
        std::cout<< reverseddigit << std::endl;
    }
    
    if (digitCount == 0)
    {
        digitCount = 1;
    }
    std::cout<< digitCount << std::endl;
    */
    
    
}