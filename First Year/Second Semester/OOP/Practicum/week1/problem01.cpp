#include <iostream>

const unsigned int maxlength = 128;

int main() {
    char str[maxlength];
    std::cin.getline(str, maxlength, '\n');

    for (unsigned int i = 0; i < maxlength; i++)
    {
        str[i] += 1;
    }
    std::cout << str << std::endl;

    return 0;
}