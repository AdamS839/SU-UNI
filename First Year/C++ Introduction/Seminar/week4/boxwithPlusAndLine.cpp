#include <iostream>

void FirstRow(int a){
    std::cout << '+';
    for (int i = 0; i < a - 2; i++)
    {
        std::cout << '-';
    }
    std::cout <<'+'<<std::endl;
}

void BoxWithPlusAndLines(int height, int width) {
    FirstRow(width);
    for (int i = 0; i < height - 2; i++) {
        std::cout << '|';
        for (int j = 0; j < width - 2; j++) {
            std::cout << ' ';
        }
        std::cout << '|' << std::endl;
    }
    FirstRow(width);
}

int main() {
    int height, width;
    std::cin >> height >> width;

    BoxWithPlusAndLines(height, width);
    
}