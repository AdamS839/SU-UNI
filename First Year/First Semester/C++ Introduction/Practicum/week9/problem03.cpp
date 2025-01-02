#include <iostream>

bool IsPowerOf2(int n){
    if (n <= 0 || n % 2 != 0) return false;
    if (n == 1) return true;
    return IsPowerOf2(n/2);
}

int main() {
    int n;
    std::cin >> n;
    std::cout <<std::boolalpha << IsPowerOf2(n) << std::endl;
    return 0;
}