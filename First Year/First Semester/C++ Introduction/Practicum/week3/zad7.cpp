#include <iostream>

int main() {
    int n, m, gcd;

    do {std::cin >> n >> m;}
    while (n <= 0 && m <= 0);

    int i = (n < m)? n : m;

    for (; i >=2 ; i--){
        if ((n % i == 0) && (m % i == 0)){
            gcd = i;
        }
    }

    std::cout << "GCD is: " << gcd << std::endl;

}