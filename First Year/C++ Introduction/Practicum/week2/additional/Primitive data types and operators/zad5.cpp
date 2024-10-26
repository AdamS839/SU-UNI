#include <iostream>

int main() {
    int number, digitEd, digitDe, digitHu, reversed;
    std::cin >> number;

    digitEd = number % 10;
    digitDe = (number / 10) % 10;
    digitHu = (number / 100) % 10; 

    reversed = digitEd * 100 + digitDe * 10 + digitHu * 1;

    if (100 <= number && 999 >= number) {
    std::cout << "Reversed number is : " << reversed << std::endl;
    }
    else std::cout<< "Number must contain only 3 digits" << std::endl;

    /*
    if (100 <= number && 999 >= number)
    {
        if (digitEd == 0)
        {
            if (digitDe == 0)
            {
                std::cout<< digitHu << std::endl;
            }
            else std::cout<< digitDe << digitHu << std::endl;
        }
        else std::cout<< digitEd << digitDe << digitHu << std::endl;
    }
    else std::cout << "Number must contain only three digits" << std::endl;
    */   
}