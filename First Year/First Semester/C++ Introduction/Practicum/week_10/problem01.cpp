#include <iostream>
#include <cstring>

bool isPalindrome(char str[], int l, int r){
    if (l >= r) return true;
    return str[l] == str[r] && isPalindrome(str, l + 1, r - 1);
}

int main() {
    char str[256];
    std::cin.getline(str, 256, '\n');
    int len = strlen(str);
    std::cout << std::boolalpha << isPalindrome(str, 0, len - 1) << std::endl;
    return 0;   
}