#include <iostream>
#include "LinkedList.hpp"
#include <vector>
#include <algorithm>

void sort(LinkedList<int> &l){
    std::vector<int> vec;
    for (auto it = l.begin(); it != l.end(); ++it){
        vec.push_back(*it);
    }
    std::sort(vec.begin(), vec.end());
    auto it = l.begin();
    for (int num : vec){
        *it = num;
        ++it;
    }
}

void printLst(LinkedList<int> l){
    for (auto it = l.begin(); it != l.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

LinkedList<int> mergesort(LinkedList<int> l1, LinkedList<int> l2){
    auto it1 = l1.begin();
    auto it2 = l2.begin();

    LinkedList<int> merged;
    while(it1 && it2){
        if(*it1 <= *it2){
            merged.push_back(*it1);
            ++it1;
        }
        else {
            merged.push_back(*it2);
            ++it2;
        }
    }
    
    while(it1){
        merged.push_back(*it1);
        ++it1;
    }

    while(it2){
        merged.push_back(*it2);
        ++it2;
    }

    return merged;
}

int main() {

    LinkedList<int> l1;
    l1.push_back(8);
    l1.push_back(3);
    l1.push_back(10);
    l1.push_back(5);
    l1.push_back(1);
    l1.push_back(12);
    l1.push_back(9);
    sort(l1);
    // printLst(l1);

    LinkedList<int> l2;
    l2.push_back(7);
    l2.push_back(4);
    l2.push_back(13);
    l2.push_back(0);
    l2.push_back(2);
    l2.push_back(11);
    sort(l2);

    LinkedList<int> merged = mergesort(l1, l2);

    printLst(merged);

    return 0;
}