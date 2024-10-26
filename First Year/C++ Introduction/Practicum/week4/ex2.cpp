#include <iostream>

int myAbs(int n){
    return n < 0 ? -1 * n : n;
}

int main() {
    std::cout << myAbs(-20) << std::endl;
}