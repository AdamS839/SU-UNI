#include <iostream>

bool isPrime(int n){
    if (n <= 1) return false;
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0) return false;
    }
    return true;
}

void primeNums(int n){
    int countPrimes = 0;
    int current = 2;
    while (countPrimes < n)
    {
        if (isPrime(current)){
            std::cout << current << " ";
            countPrimes++;
        }
        current++;
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cin >> n;

    primeNums(n);
}