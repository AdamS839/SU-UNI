#include <iostream>

int targetDigitCount(int num, int targetDigit){
    int countTarget = 0;
    while (num > 0)
    {
        int digit = num % 10;
        if (digit == targetDigit)
        {
            countTarget++;
        }
        num /= 10;
    }
    return countTarget;
}

int main() {
    int num, targetDigit;
    std::cin >> num >> targetDigit;

    std::cout << targetDigitCount(num, targetDigit) <<std::endl;
}