#include <iostream>

int getStrSize(char str[]){
    int size = 0;
    while (str[size] != '\0')
    {
        ++size;
    }
    return size;
}

int main() {
    char str[51];
    std::cin.getline(str, 51);

    for (char i = 0; i < getStrSize(str); i++){
        if (str[i] >= 'A' && str[i] <= 'Z'){
            str[i] += 'a' - 'A';
        }
    }
    
    std::cout << str << std::endl;
    
}