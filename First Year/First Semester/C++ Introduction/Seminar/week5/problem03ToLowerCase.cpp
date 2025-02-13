#include <iostream>
//#include <cstring>

int StrLength(char str[]){
    int size = 0;
    while (str[size] != '\0')
    {
        ++size;
    }
    return size;
}

void changeLetters(char str[]){
    for (char i = 0; i < StrLength(str); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z'){
            str[i] += 'a' - 'A';
        }
        else if(str[i] <= 'A' && str[i] >= 'Z') {
            str[i] += 'A' - 'a';
        }
        std::cout << str[i];
    }
    std::cout << std::endl;
}

int main() {
    char str[100];
    std::cin.getline(str, 100, '\n');


    std::cout << "Size of the string is: "<< StrLength(str) << std::endl;
    //std::cout << "Size of the string is: " << std::strlen(str) << std::endl;
    changeLetters(str);
}