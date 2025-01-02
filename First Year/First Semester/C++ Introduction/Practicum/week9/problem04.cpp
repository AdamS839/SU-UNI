#include <iostream>

int steps(int n){
    if (n == 0) return 1;
    if (n < 0) return 0;
    return steps(n - 1) + steps(n - 2);
}

int main() {
    int n;
    std::cin >> n;
    std::cout << steps(n) << std::endl;
    return 0;
}