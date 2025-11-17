#include <iostream>
#include "LinkedList.hpp"

template <class T>
void LinkedList<T>::reorder(){
    if(empty() || m_begin == m_end) return;

    // find second part of list
    Node *slow = m_begin;
    Node *fast = m_begin;
    while (fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    
    Node *secondPart = slow->next;
    slow->next = nullptr;

    Node *prev = nullptr;
    Node *curr = secondPart;
    while(curr){
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    Node *firstPtr = m_begin;
    Node *secondPtr = prev;

    while(secondPtr){
        Node *temp1 = firstPtr->next;
        Node *temp2 = secondPtr->next;

        firstPtr->next = secondPtr;
        secondPtr->next = temp1;

        firstPtr = temp1;
        secondPtr = temp2;
    }

}

int main() {
    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    l.push_back(7);
    l.push_back(8);
    l.push_back(9);
    l.push_back(10);
    l.reorder();
    while(!l.empty()){
        std::cout << l.pop_front() << " ";
    }
    std::cout << std::endl;
    return 0;
}