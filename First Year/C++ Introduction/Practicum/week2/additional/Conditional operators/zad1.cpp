#include <iostream>

int main(){
    int a;
    std::cin >> a;
    if (a > 0) std::cout<<"Number is positive" << std::endl;
    else if (a < 0) std::cout<< "Number is negative" << std::endl;
    else if (a == 0) std::cout << "Number is 0" << std::endl;

    if (a % 2 == 0) std::cout<< "Number is even\n";
    else std::cout<< "Number is odd\n"; 
}