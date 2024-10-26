#include <iostream>

int main() {
    int a;
    std::cin >> a;

    
    int firstD, secondD, thirdD, forthD;
    forthD = a % 10;
    thirdD = (a / 10) % 10;
    secondD = (a / 100) % 10;
    firstD = (a / 1000) % 10;

    /* Checking for each digit of the number
    std:: cout<< firstD  << std::endl;
    std:: cout<< secondD  << std::endl;
    std:: cout<< thirdD  << std::endl;
    std:: cout<< forthD  << std::endl;
    */

    if (a > 999 && a <= 9999){
        if (firstD < secondD < thirdD < forthD)
        {
            std::cout << forthD << thirdD << secondD << firstD;
        }
        else std:: cout << a * 2;
    }
    else std:: cout << "Number must only contain 4 digits.";
    
}