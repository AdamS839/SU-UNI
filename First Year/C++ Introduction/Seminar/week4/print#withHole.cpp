#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;

    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (i == 0 || i == a - 1 || j == 0 || j == b-1)
            {
                std::cout<< '#';
            }
            else std::cout<< ' ';
            
        }
        std::cout<<std::endl;    
    }

    
}