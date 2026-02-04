#include <iostream>
#include <list>

template<typename T>
bool isPalindrome(std::list<T> const &list){
    if (list.empty()) return true;
    auto b = list.begin();
    auto e = list.end();
    --e;
    while (b != e && b != std::next(e)){
        if (*b != *e){
            return false;
        }
        ++b;
        if (b == e) break;
        --e;
    }
    return true;
}

template<typename T>
int countPalindrome(std::list<std::list<T>> const &doublelist){
    if (doublelist.empty()) return 0;
    int counter = 0;
    auto it = doublelist.begin();

    while (it != doublelist.end()){
        if (isPalindrome(*it)) counter++;
        ++it;
    }

    return counter;
}

int main() {
    std::cout << std::boolalpha;

    // std::list<int> l = {1,2,3,2,1};
    // std::cout << isPalindrome(l) << '\n';

    std::list<std::list<int>> l1 = {
        {1,2,3,2,1},
        {5,6,7,8,9},
        {4,5,4,5,5,4,5,4},
        {1,2,2,1},
        {1,2,3}
    };

    std::cout << countPalindrome(l1) << '\n';

    return 0;
}