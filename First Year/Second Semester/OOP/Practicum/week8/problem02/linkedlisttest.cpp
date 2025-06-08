#include "LinkedList.hpp"

int main() {

    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);

    list.push_back(8);


    // std::cout << "List after pushing back 8: ";
    // for (int i : list) {
    //     std::cout << i << ' ';
    // }
    // std::cout << std::endl;

    for (LinkedList<int>::reverseiterator it = list.rbegin(); it != list.rend(); ++it){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    for (LinkedList<int>::iterator it = list.begin(); it != list.end(); ++it){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    return 0;
}