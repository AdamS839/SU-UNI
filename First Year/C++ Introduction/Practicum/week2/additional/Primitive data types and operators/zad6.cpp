#include <iostream>

int main() {
    int year;

    std:: cin >> year;
    
    if ((year % 4 == 0 && year % 100 != 0)|| year % 400 == 0)
    {
        std::cout<< "Year is leap year" << std::endl;
    }
    else std::cout << "Year is not leap year" << std::endl;
    
}