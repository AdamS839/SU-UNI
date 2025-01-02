#include <iostream>

int TripleFact(int n){
    if (n <= 0) return 1;
    return n * TripleFact(n-3);
}

int main() {
    int n;
    std::cin >> n;
    if (n < 0) return 1;
    std::cout << TripleFact(n) << std::endl;
    return 0;
}