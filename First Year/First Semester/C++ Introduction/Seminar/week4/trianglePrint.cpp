#include <iostream>

void Triangle(int n){
    for (int i = 0; i <= n - 1; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            std::cout << '#';
        }
        std::cout<<std::endl;
    }
}

void ReverseTriangle(int n){
    for (int i = n; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            std::cout << '#';
        }
        std::cout<<std::endl;
    }   
}


int main() {
    int lines;
    std::cin >> lines;

    //Triangle(lines);
    ReverseTriangle(lines);
}