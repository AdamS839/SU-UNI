#include <iostream>
#include "testLinkedList.hpp"

template <class T>
TestList<T> TestList<T>::merge_sort(const TestList<T> &one, const TestList<T> &two){
    TestList<T> result;
    TestList<T>::Node *p = one.m_begin;
    TestList<T>::Node *q = two.m_begin;

    while(p && q){
        if(p->data <= q->data){
            result.push_back(p->data);
            p = p->next;
        }
        else{
            result.push_back(q->data);
            q = q->next;
        }
    }

    while(p){
        result.push_back(p->data);
        p = p->next;
    }
    while(q){
        result.push_back(q->data);
        q = q->next;
    }
    return result;
}

int main(){

    TestList<int> l1({1,3,5,7,9});
    TestList<int> l2({2,4,6,8,10});
    TestList<int> res = TestList<int>::merge_sort(l1, l2);

    while (!res.empty()) {
        std::cout << res.pop_front() << " ";
    }

    return 0;
}