#include <iostream>
#include <cstring>

int toNum(char const* str){
    int result = 0;
    int counter = 0;
    bool negativeN = false;

    while (str[counter] == ' ' || str[counter] == '+'){
        ++counter;
    }

    if (str[counter] == '-'){
        negativeN = true;
        ++counter;
    }
    
    while (str[counter] != '\0' && str[counter] >= '0' && str[counter] <= '9'){
        result = result * 10 + (str[counter] - '0');
        ++counter;
    }
    
    if (negativeN){
        return -result;
    }
    else return result;
}

int main() {
    char str[51];
    int result = 0;
    int counter = 0;
    int size = strlen(str);
    std::cin.getline(str, 51);

    std::cout << toNum(str) <<std::endl;
}