#include <iostream>

int countDigits(int n){
    int counter = 0;
    while (n > 0)
    {
        n /= 10;
        counter++;
    }
    return counter;
    
}

bool isArmstrong(int n){
    int num = n;
    int sum = 0;
    int numDigit = countDigits(n);
    while (num > 0)
    {
        int digit = num % 10;
        int multiplied = 1;
        for (int i = 0; i < numDigit; i++)
        {
            multiplied *= digit;
        }
        sum += multiplied;
        num /= 10;
    }

    if (sum == n) return true;
    else return false;
}


int main() {
    int n;
    std::cin >> n;
    std::cout <<std::boolalpha << isArmstrong(n) << std::endl;
}