#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            std::cout<<"#";
        }
        std::cout<<std::endl;
    }
    
}