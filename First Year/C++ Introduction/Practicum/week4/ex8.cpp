#include <iostream>

int Pow(int a, int b){
    int multiplied = 1; 
    for (int i = 0; i < b; i++)
    {
        multiplied *= a;
    }
    return multiplied;
    
}

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << Pow(a, b) << std::endl;
}