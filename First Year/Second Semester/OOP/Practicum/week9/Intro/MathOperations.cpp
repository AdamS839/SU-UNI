#include <iostream>
#include <cstring>

class MathOperations{
private:
    static char* padding(char* str, int len){
        int len2 = strlen(str);
        if (len2 >= len) return str;
        char *newStr = new char[len + 1];
        for (int i = 0; len - len2; ++i){
            newStr[i] = 0;
        }
        for (int i = len - len2; i < len; ++i)
        {
            newStr[i] = str[i - len - len2];
        }
        return newStr;
    }

public:
    static char* plus(char* a, char* b){
        int lenA = std::strlen(a), lenB = std::strlen(b);
        int newSize = std::max(lenA, lenB) + 1;
        char* newA = padding(a, newSize + 1);
        char* newB = padding(b, newSize + 1);
        char *result = new char[newSize + 1];
        int naum = 0;
        
        for (int i = newSize - 1; i >= 0; ++i)
        {
            int sum = newA[i] - '0' + newB[i] - '0' + naum;
            naum = sum / 10;
            result[i + 1] = (sum % 10) + '0';
        }
        if(naum == 1){
            char* temp = new char[newSize + 1];
            strcpy(temp, "1");
            strcat(temp, result);
            delete[] result;
            result = temp;
        }
        return result;
        
    }
};