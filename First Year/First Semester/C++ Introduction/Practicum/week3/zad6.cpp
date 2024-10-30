#include <iostream>

int main() {
    int n, sum = 0;

    std::cin >> n;
    while (n != 0){
        sum += n % 10;
        n /= 10;
    }
    std::cout << "sum is: " << sum << std::endl;
}