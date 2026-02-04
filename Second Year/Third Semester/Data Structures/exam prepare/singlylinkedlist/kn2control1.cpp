#include <iostream>
#include "LinkedList.hpp"
#include <stack>


template<typename T>
void reevaluate(LinkedList<std::stack<T>> &list){
    if (list.empty() || list.size() == 1) return;

    std::stack<T> tempStack;

    auto it = list.begin();
    int pos = 0;

    while(it){
        if (pos % 2 == 0){
            std::stack<T> currStack = *it;
            
            // !!!!!!!!!!!!!!!!!!!!!!!
            while (!currStack.empty()){
                T curr = currStack.top();
                currStack.pop();

                while(!tempStack.empty() && tempStack.top() < curr){
                    currStack.push(tempStack.top());
                    tempStack.pop();
                }
                tempStack.push(curr);
            }
            // !!!!!!!!!!!!!!!!!!!!!!!
        }
        ++it;
        pos++;
    }

    std::stack<T> final;
    while(!tempStack.empty()){
        final.push(tempStack.top());
        tempStack.pop();
    }

    LinkedList<std::stack<T>> newList;
    newList.push_back(final);
    it = list.begin();
    pos = 0;
    while(it){
        if (pos % 2 != 0){
            newList.push_back(*it);
        }
        ++it;
        pos++;
    }
    list = std::move(newList);
}

void printStack(std::stack<int> s) {
    std::stack<int> temp;
    // Reverse order to print from bottom to top
    while (!s.empty()) {
        temp.push(s.top());
        s.pop();
    }
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
}


template <class T>
void printList(LinkedList<T> &list) {
    int index = 0;
    for (auto it = list.begin(); it != list.end(); ++it, ++index) {
        std::cout << "Stack " << index+1 << ": ";
        printStack(*it);
        std::cout << "\n";
    }
}


int main() {

    std::stack<int> one;
    one.push(1); one.push(2); one.push(3);
    std::stack<int> two;
    two.push(0); two.push(3);
    std::stack<int> three;
    three.push(-1); three.push(0); three.push(2); three.push(4);
    std::stack<int> four;
    four.push(0); four.push(4); four.push(7);
    std::stack<int> five;
    five.push(-5); five.push(-10); five.push(14); five.push(420);

    LinkedList<std::stack<int>> list;
    list.push_back(one); list.push_back(two); list.push_back(three); list.push_back(four); list.push_back(five);
    
    std::cout << "Before reevaluate:\n";
    printList(list);

    reevaluate(list);

    std::cout << "\nAfter reevaluate:\n";
    printList(list);

    return 0;
}