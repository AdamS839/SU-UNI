#include <iostream>
#include "LinkedList.hpp"

template<typename T>
void LinkedList<T>::reverse(){
    if (empty() || m_begin == m_end) return;

    Node *prev = nullptr;
    Node *curr = m_begin;
    m_end = m_begin;

    while (curr){
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    m_begin = prev;
}

int main() {

    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.reverse();
    for (int el : l){
        std::cout << el << ' ';
    }
    std::cout << std::endl;

    return 0;
}