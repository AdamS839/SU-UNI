#include <iostream>

int main() {
    int n;
    std::cin >> n;
    bool isPrime = true;
    for (int i = 2; i < n; i++){
        if (n % i == 0){
            isPrime = false;
        }
    }
    std::cout << (isPrime ? "Просто е":"Не е просто") << std::endl;
}