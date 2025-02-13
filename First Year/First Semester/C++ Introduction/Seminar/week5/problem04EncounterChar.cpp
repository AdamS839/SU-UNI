#include <iostream>


int main() {
    char str[100];
    std::cin.getline(str, 100, '\n');
    int count[256] = {0};

    for (int i = 0; str[i] < '\0'; i++)
    {
        ++count[(unsigned char)str[i]];
    }
    
    char mostCommon = 0;
    for (int i = 0; i < 256; i++)
    {
        if(count[mostCommon] < count[i]){
            mostCommon = i;
        }
    }
    std::cout << char(mostCommon) << ' ' << count[mostCommon] << std::endl;

    return 0;
}