#include <iostream>

int dividerSum(int n){
    int sum = 0;
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0){
            sum += i;
        }
    }
    return sum;
}

bool isPerfect(int n){
    if (n == dividerSum(n)) 
    {
        return true;
    }
    else return false;
    
}

int main() {
    int n;
    std::cin >> n;
    std::cout << dividerSum(n) << std::endl;
    std::cout << std::boolalpha << isPerfect(n) << std::endl;
}