#include <iostream>

bool IsItTriangle(int a, int b, int c){
    return (a + b > c) && (a + c > b) && (c + b > a);
}

int main() {
    int perimeter;
    
    do (std::cin >> perimeter);
    while (perimeter <= 0);

    //без дублиране на тригълници
    for (int a = 1; a <= perimeter / 2; a++){
        for (int b = a; b <= (perimeter - a) / 2; b++){
            int c = perimeter - a - b;
            if (c > 0 && IsItTriangle(a, b, c)) // проверяваме дали a, b и c могат да бъдат страни на триъгълника
            {
                std::cout << a << ", " << b << ", " << c << std::endl;
            }
        }
    }
    
    
}