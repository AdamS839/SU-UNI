#include <iostream>

int main() {
    int num, checkNum = num;

    std::cin >> num;

    if(num <= 0){
        std::cout << "Number isnt power of 2";
        return 0;
    }

    while(checkNum % 2 == 0){
        checkNum /= 2;
        }
    if (checkNum == 1) {
        std::cout << "Number is power of 2" << std::endl;
    }
    else std::cout << "Number is not power of 2" << std::endl;  
}
