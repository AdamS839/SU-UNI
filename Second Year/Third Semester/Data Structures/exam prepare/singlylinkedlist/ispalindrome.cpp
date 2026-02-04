#include <iostream>
#include "LinkedList.hpp"

template<typename T>
bool LinkedList<T>::isPalindrome(){
    if (empty() || m_begin == m_end) return true;

    // find middle
    Node *slow = m_begin;
    Node *fast = m_begin;
    while (fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    // reverse from middle to end
    Node *prev = nullptr;
    Node *curr = slow->next;
    while (curr){
        Node *next =curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    Node *secondPart = prev;
    
    // check for palindrome for while the second part is not nullptr
    Node *leftP = m_begin;
    Node *rightP = secondPart;
    bool found = true;
    while (rightP){
        if (leftP->data != rightP->data){
            found = false;
            break;
        }
        leftP = leftP->next;
        rightP = rightP->next;
    }

    // reverse back
    curr = secondPart;
    prev = nullptr;
    while(curr){
        Node *next =curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    slow->next = prev;

    // return true/false
    return found;
}

int main() {

    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(3);
    l.push_back(2);
    l.push_back(1);

    std::cout << std::boolalpha << l.isPalindrome() << std::endl;

    return 0;
}