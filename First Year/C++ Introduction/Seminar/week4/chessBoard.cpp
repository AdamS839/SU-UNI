#include <iostream>

void PrintFirstRowOfChessboard(int a){
    std::cout << ' ';
    for (int i = 0; i < a; i++)
    {
        std::cout << '-';
    }
    std::cout <<std::endl;
}

void PrintChessboard(int a){
    PrintFirstRowOfChessboard(a);
    for (int i = 0; i < a; i++)
    {
        std::cout << "|";
        for (int j = 0; j < a; j++)
        {
            if((i + j) % 2 == 0){
                std::cout <<'#';
            }
            else std::cout << ' ';
        }
        std::cout << "|" << std::endl;
    }
    PrintFirstRowOfChessboard(a);
}
int main() {
    int a;
    std::cin >> a;
    PrintChessboard(a);
}