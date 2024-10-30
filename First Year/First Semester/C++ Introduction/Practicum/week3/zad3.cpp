#include <iostream>

int main() {
    int n, fact = 1;

    do { std::cin >> n; }
    while (n < 0);

    /* Factoriel
    for (int i = 1; i <= n; i++){
        fact *= i;
    }
    */

    //Double Factoriel
    for (int i = n; i >= 2; i -=2){
        fact *= i;
    }

    std::cout << "Factoriel is: " << fact << std::endl;
}