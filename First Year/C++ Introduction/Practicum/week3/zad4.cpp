#include <iostream>

long long Fibonacci(long long n){
    long long f1 = 0;
    long long f2 = 1;
    long long f3;

    if (n == 0)
    {
        return 0;
    }
    else if (n == 1) return 1;

    for (long long i = 2; i <= n; i++)
    {
        f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
    }

    return f2;
}

int main() {
    long long n;

    do {std::cin >> n; }
    while (n < 0);

    std::cout << "The " << n << " Fibonacci number is: " << Fibonacci(n) << std::endl;        
}