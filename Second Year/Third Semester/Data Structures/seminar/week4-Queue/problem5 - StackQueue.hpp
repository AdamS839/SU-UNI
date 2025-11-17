#ifndef __StackQueue_HPP
#define __StackQueue_HPP
#include <stack>
#include <stdexcept>


template<class T>
class Queue{
private:
std::stack<T> s1, s2;

void reverse(){
    if(s2.empty()){
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
    }
}

public:
bool empty() const{
    return s1.empty() && s2.empty();
}

std::size_t size() const{
    return s1.size() + s2.size();
}

void push(T const &data){
    if(empty()){
        s2.push(data);
    }
    else s1.push(data);
}

void pop(){
    if(empty()){
        throw std::runtime_error("empty queue");
    }
    reverse();
    s2.pop();
}

T const &top() const{
    if(empty()) throw std::runtime_error("empty queue");
    return s2.top();
}

T &top() {
    if(empty()) throw std::runtime_error("empty queue");
    return s2.top();
}

};

#endif