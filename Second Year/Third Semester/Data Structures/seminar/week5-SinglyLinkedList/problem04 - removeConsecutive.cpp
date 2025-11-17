#include <iostream>
#include "testLinkedList.hpp"

template <class T>
void TestList<T>::removeConsecutive(){
    if(empty() || size() == 1){
        return;
    }
    Node *curr = m_begin;
    while(curr && curr->next){
        if(curr->data == curr->next->data){
            Node *dupe = curr->next;
            curr->next = curr->next->next;
            delete dupe;
            m_size--;
        }
        else{
            curr = curr->next;
        }
    }
    m_end = curr;
}

int main(){

    TestList<int> l({1,1,2,3,3,3,3,4,1,1});
    l.removeConsecutive();
    while (!l.empty()) {
        std::cout << l.pop_front() << " ";
    }

    return 0;
}