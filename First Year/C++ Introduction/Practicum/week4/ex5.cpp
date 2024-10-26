#include <iostream>

bool isMersenne(int num){
    if (num < 2) return false;
    num += 1;
    if ((num & (num - 1)) == 0)
    {
        return true;
    }
    else return false;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << std::boolalpha << isMersenne(n) << std::endl;;
}