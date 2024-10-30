#include <iostream>

int main() {
    int n, s = 0;
    std::cin >> n;
    
    /*
    for (int i = 1; i <= n; i++)
    {
        s += i;
    }
    std::cout << "Sum is: " << s << std::endl;
    */
    s = (n * (n - 1)) / 2;
    std::cout << "Sum is: " << s << std::endl;
}