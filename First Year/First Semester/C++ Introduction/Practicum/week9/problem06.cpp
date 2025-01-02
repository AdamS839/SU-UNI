#include <iostream>

void printRow(int n){
    std::cout << n << ' ';
    
    if (n == 1) {
        return;
    }
    if (n % 2 == 0){
        printRow(n/2);
    } 
    if (n % 2 != 0){
        printRow(3*n+1); 
    }
}

int main() {
    int n;
    std::cin >> n;
    printRow(n);
    return 0;
}