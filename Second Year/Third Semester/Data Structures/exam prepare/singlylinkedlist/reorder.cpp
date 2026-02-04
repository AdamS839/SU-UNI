#include <iostream>
#include "LinkedList.hpp"

template<typename T>
void LinkedList<T>::reorder(){
    if (empty() || m_begin == m_end) return;

    Node *slow = m_begin;
    Node *fast = m_begin;

    while (fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    Node *sec = slow->next;
    slow->next = nullptr;

    Node *prev = nullptr;
    Node *curr = sec;
    while (curr){
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    Node *first =m_begin;
    Node *second = prev;

    while(second){
        Node *tmp1 = first->next;
        Node *tmp2 = second->next;

        first->next = second;
        second->next = tmp1;

        first = tmp1;
        second = tmp2;
    }

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
    l1.push_back(6);
    l1.push_back(7);
    l1.push_back(8);
    l1.push_back(9);
    l1.push_back(10);

    l1.reorder();
    printLst(l1);


    return 0;
}
