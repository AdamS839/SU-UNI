#include <iostream>
#include "testLinkedList.hpp"
#include "LinkedList.hpp"

template <class T>
void TestList<T>::reverse(){
    if(empty() || m_begin == m_end) return;
    Node *prev = nullptr;
    Node *curr = m_begin;
    m_end = m_begin;

    while(curr){
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    m_begin = prev;
}

template <class T>
void LinkedList<T>::reverseConst(){
    if (empty() || m_begin == m_end) return;
    Node *prev = nullptr;
    Node *curr = m_begin; // it
    m_end = m_begin;

    while (curr){
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    m_begin = prev; // or it = prev
}

int main(){
    TestList<int> tl;
    tl.push_back(1);
    tl.push_back(2);
    tl.push_back(3);
    tl.reverse();
    while (!tl.empty()) {
        std::cout << tl.pop_front() << " ";
    }
    std::cout << std::endl;
    return 0;
}