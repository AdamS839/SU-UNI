#include <iostream>
#include <cstring>

void caesarCipher(char *src, int shift){
    int len = std::strlen(src);
    if (shift < -26 || shift > 26){
        shift %= 26;
    }
    int index = 0;
    while (index < len)
    {
        char letter = src[index];
        if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
        {
            char cipherbase = (letter >= 'A' && letter <= 'Z') ? 'A' : 'a'; //upper of lower case
            int offset = letter - cipherbase;
            offset = (offset + shift + 26) % 26;
            src[index] = cipherbase + offset;
        }
        ++index;
    }
}

int main() {
    char str[1025];
    int shift;
    std::cin.getline(str, 1025);
    std::cin >> shift;
    caesarCipher(str, shift);
    std::cout << str << std::endl;

    return 0;
}