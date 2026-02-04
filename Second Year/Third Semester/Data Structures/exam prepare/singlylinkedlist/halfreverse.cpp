#include <iostream>
#include "LinkedList.hpp"

template<typename T>
void LinkedList<T>::rearrange(){
    if (empty() || m_begin == m_end) return;

    Node *slow = m_begin;
    Node *fast = m_begin;

    while (fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    Node *secPart = slow->next;
    slow->next = nullptr;

    Node *prev = nullptr;
    Node *curr = secPart;
    while(curr){
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    Node *newHead = prev;
    Node *newTail = prev;
    while (newTail && newTail->next){
        newTail = newTail->next;
    }
    if (newTail) newTail->next = m_begin;
    m_begin = newHead;
}

void printLst(LinkedList<int> l){
    for(auto it = l.begin(); it != l.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {

    LinkedList<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    
    l1.rearrange();

    printLst(l1);


    return 0;
}