#include <iostream>
#include <cstring>

bool isPalindrome(const char *str, int start, int end){
    while (start < end)
    {
        if(str[start] != str[end]){
            return false;
        }
        ++start;
        --end;
    }
    return true;
}

int longestPalindromeLength(const char *str){
    int maxLength = 0;
    int len = std::strlen(str);

    for (int start = 0; start < len; start++){
        for (int end = start; end < len; end++){
            if(isPalindrome(str, start, end)){
                int current = end - start + 1;
                if(current > maxLength){
                    maxLength = current;
                }
            }
        }
    }
    return maxLength;
    
}

int main() {
    char str[100];
    std::cin.getline(str,100);

    std::cout << longestPalindromeLength(str) << std::endl;

    return 0;
}