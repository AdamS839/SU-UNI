#include <iostream>

int reverseN(int n){
    int digitReverse = 0;
    while (n > 0)
    {
        digitReverse = digitReverse * 10 + (n % 10);
        n /= 10;
    }
    return digitReverse;
}

int main() {
    int n;
    std::cin >> n;
    std::cout<< reverseN(n) << std::endl;
}