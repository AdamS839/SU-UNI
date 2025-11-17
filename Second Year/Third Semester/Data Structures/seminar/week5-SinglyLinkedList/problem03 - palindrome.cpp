#include <iostream>
#include "testLinkedList.hpp"


template <class T>
bool TestList<T>::isPalindrome() const{
    if(!m_begin || !m_begin->next){
        return true;
    }

    Node *slow = m_begin;
    Node *fast = m_begin;
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    // reverse second
    Node* prev = nullptr;
    Node* curr = slow->next;
    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    Node* secondHalf = prev;

    // check palindrome
    Node *left = m_begin;
    Node *right = secondHalf;
    bool isPalim = true;
    while(right){
        if(left->data != right->data){
            isPalim = false;
            break;
        }
        left = left->next;
        right = right->next;
    }

    //reverse back second
    curr = secondHalf;
    prev = nullptr;
    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    slow->next = prev; 

    // return boolean
    return isPalim;
}

int main(){
    TestList<int> tl;
    tl.push_back(1);
    tl.push_back(2);
    tl.push_back(3);
    tl.push_back(4);
    tl.push_back(3);
    tl.push_back(2);
    tl.push_back(1);
    std::cout << tl.isPalindrome() << std::endl;
    
    return 0;
}