#include <iostream>
#include <cstring>

bool matchPattern(const char *pattern, char *text) {
    int i = 0; 
    int j = 0; 
    int starIndex = -1;
    int textIndex = -1;

    while (text[i] != '\0') {
        if (pattern[j] == text[i] || pattern[j] == '.') {
            i++;
            j++;
        }
        else if (pattern[j] == '*') {
            starIndex = j;
            textIndex = i;
            ++j;
        }
        else if (starIndex != -1) {
            j = starIndex + 1;
            i = textIndex + 1;
            textIndex = i;
        }
        else {
            return false;
        }
    }

    while (pattern[j] == '*') {
        j++;
    }

    return pattern[j] == '\0';
}

int main() {
    char pattern[1025];
    char text[1025];

    std::cin.getline(pattern, 1025);

    std::cin.getline(text, 1025);

    std::cout << std::boolalpha << matchPattern(pattern, text) << std::endl;
    
    return 0;
}
