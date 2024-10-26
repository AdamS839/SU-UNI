#include <iostream>

int reverseN(int n){
    int digitReverse = 0;
    while (n > 0)
    {
        digitReverse = digitReverse * 10 + (n % 10);
        n /= 10;
    }
    return digitReverse;
}

bool isPalindrome(int n){
    return n == reverseN(n) ? true : false;
}

int main() {
    int n;
    std::cin >> n;
    std::cout<< std::boolalpha << isPalindrome(n) << std::endl;
}