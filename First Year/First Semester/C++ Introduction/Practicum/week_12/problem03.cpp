#include <iostream>
#include <cstring>

int const size = 100;

int main() {
    char str[size];
    do
    {
        std::cin.getline(str, size, ' ');
    } while (strcmp(str, "stop") != 0);
    
    

    return 0;
}