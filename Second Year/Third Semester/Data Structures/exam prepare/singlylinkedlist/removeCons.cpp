#include <iostream>
#include "LinkedList.hpp"


void removeConsecutive(LinkedList<int> &l){
    if (l.empty()) return;

    LinkedList<int> temp;
    int prev = l.pop_front();
    temp.push_back(prev);

    while(!l.empty()){
        int curr = l.pop_front();
        if (curr != prev){
            temp.push_back(curr);
        }
        prev = curr;
    }   

    l = std::move(temp);
}

int main() {

    LinkedList<int> l;
    l.push_back(1);
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(3);
    l.push_back(3);
    l.push_back(4);
    l.push_back(4);
    l.push_back(1);
    l.push_back(1);

    removeConsecutive(l);

    while(!l.empty()){
        std::cout << l.pop_front() << " ";
    }
    std::cout << std::endl;

    return 0;
}