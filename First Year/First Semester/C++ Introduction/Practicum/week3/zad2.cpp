#include <iostream>

int main() {
    int n, input, s = 0, result;
    
    std::cin >> n;
    do {std::cin >> n; }
    while (n <= 0);

    for (int i = 1; i <= n; i++){
        std::cin >> input;
        s += input;
    }

    result = s / n;
    std::cout << "Result is: " << result << std::endl;

}