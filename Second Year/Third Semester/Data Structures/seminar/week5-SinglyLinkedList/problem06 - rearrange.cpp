#include <iostream>
#include "LinkedList.hpp"

template <class T>
void LinkedList<T>::rearrange(){
    //check if empty or 1 element
    if (empty() || m_begin == m_end) return;

    Node *slow = m_begin;
    Node *fast = m_begin;

    // find the second part
    while (fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    // get the second part
    Node *secondPart = slow->next;
    slow->next = nullptr;

    // reverse the second part of the list
    Node *prev = nullptr;
    Node *curr = secondPart;
    while(curr){
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    //attach second part to first
    Node *newHead = prev; // първия елемент от обърнатата втора част
    Node *tail = prev;
    while(tail && tail->next){
        tail = tail->next; // преместваме указателя на опашката до последния елемент на обърнатата чат
    }
    if(tail) tail->next = m_begin; // от обърнатата част казваме че опашката ще сочи към първоначалния лист
    m_begin = newHead; // сменяме началото да бъде новата глава
}

int main() {
    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.rearrange();
    while(!l.empty()){
        std::cout << l.pop_front() << " ";
    }
    std::cout << std::endl;
    return 0;
}