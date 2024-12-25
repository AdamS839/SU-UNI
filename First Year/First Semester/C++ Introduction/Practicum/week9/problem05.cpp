#include <iostream>
int fastPower(int x, int n){
    if (n == 0) return 1;
    if (x == 0) return 0;
    if (n % 2 == 0) return fastPower(x*x,(n/2));
    else return x*fastPower(x, n-1);
}

int main() {
    int n, x;
    std::cin >> x >> n;
    std::cout << fastPower(x, n) << std::endl;
    return 0;
}