#include <iostream>
#include <cstring>

void changeNums(char *str){
    int index = 0;
    bool inNumber = false;
    int len = std::strlen(str);

    while (str[index] != '\0')
    {
        if (str[index] >= '0' && str[index] <= '9' && index + 1 < len && str[index + 1] >= '0' && str[index + 1] <= '9') {
            str[index] = '#';
            for (int i = index + 1; i < len; ++i) {
                str[i] = str[i + 1];
            }
            len--;
        } else if (str[index] >= '0' && str[index] <= '9') {
            str[index] = '#';
        }
        index++;
    }

}
int main() {
    char str[100];
    std::cin.getline(str, 100);

    changeNums(str);
    std::cout << str << std::endl;

    return 0;
}
