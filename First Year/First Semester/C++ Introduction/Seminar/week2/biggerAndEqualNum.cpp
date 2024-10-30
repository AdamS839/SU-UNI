#include <iostream>

int main() {
    int a, b, c;

    std::cin >> a >> b >> c;

    if (a == b || a == c || b == c)
    {
        if (a == b && c > a)
        {
            std:: cout << "A = B" << std:: endl;
            std:: cout << "C is biggest number";
        }
        else if (a == c && b > a)
        {
            std:: cout << "A = C" << std:: endl;
            std:: cout << "B is biggest number";
        }
        else if (b == c && a > b)
        {
            std:: cout << "B = C" << std:: endl;
            std:: cout << "A is biggest number";
        }
    }
    else {
        if (a > b && a > c)
        {
            std:: cout << "A is biggest number";
        }
        else if (b > a && b > c)
        {
            std:: cout << "B is biggest number";
        }
        else std:: cout << "C is biggest number";
    }
    
    
}