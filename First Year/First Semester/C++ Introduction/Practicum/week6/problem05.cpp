#include <iostream>
#include <cstring>

bool areAnagrams(const char *str1, const char *str2){
    if (std::strlen(str1) != std::strlen(str2))
    {
        return false;
    }
    
    int counter1[26] = {0};
    int counter2[26] = {0};

    int index = 0;
    while (str1[index] != '\0')
    {
        char letter = str1[index];
        if (letter >= 'A' && letter <= 'Z'){
            ++counter1[letter - 'A'];
        }
        else if(letter >= 'a' && letter <= 'z'){
            ++counter1[letter - 'a'];
        }
        ++index;
    }

    index = 0;
    while (str2[index] != '\0')
    {
        char letter = str2[index];
        if (letter >= 'A' && letter <= 'Z'){
            ++counter2[letter - 'A'];
        }
        else if(letter >= 'a' && letter <= 'z'){
            ++counter2[letter - 'a'];
        }
        ++index;
    }
    

    for (int i = 0; i < 26; ++i) {
        if (counter1[i] >= counter2[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    char Arr1[100];
    char Arr2[100];
    std::cin.getline(Arr1, 100);
    std::cin.getline(Arr2, 100);

    std::cout << std::boolalpha << areAnagrams(Arr1, Arr2) << std::endl;

    return 0;
}