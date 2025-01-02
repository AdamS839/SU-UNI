#include <iostream>

int strlen(char const* str){
    int size = 0;
    while (str[size] != '\0')
    {
        ++size;
    }
    return size;
}

void strcpy(char* dest, char const* source){
    int counter = 0;
    while (source[counter] != '\0') // source[counter] will make dest bigger
    {
        dest[counter] = source[counter];
        ++counter;
    }
    dest[counter] = '\0';
}

void strcat(char* dest, char const* source){
    int counter = 0;
    int destSize = strlen(dest);
    while (source[counter] != '\0')
    {
        dest[destSize + counter] = source[counter];
        ++counter;
    }
}

int strcmp(char const* s1, char const* s2){
    int sizeofS1 = strlen(s1);
    int sizeofS2 = strlen(s2);
    
    int size;
    if (sizeofS1 >= sizeofS2)
    {
        size = sizeofS2;
    }
    else size = sizeofS1;
    

    for (int i = 0; i < size; i++)
    {
        if(s1[i] < s2[i]){
            return -1;
        }
        else if(s1[i] > s2[i]){
            return 1;
        }
    }
    
    if(sizeofS1 < sizeofS2){
        return -1;
    }
    else if(sizeofS1 > sizeofS2){
        return 1;
    }
    else return 0;

}

int main() {
    char str1[7] = "World ";
    char str2[7] = "b lack";
    //std::cin.getline(str1, 121);
    //std::cout<< strlen(source) << std::endl;
    
    //strcpy(str1, str2);
    //std::cout << str1 << std::endl;

    strcat(str1, str2);
    std::cout << str1 <<std::endl;

    //std::cout << strcmp(str1, str2) << std::endl;
}