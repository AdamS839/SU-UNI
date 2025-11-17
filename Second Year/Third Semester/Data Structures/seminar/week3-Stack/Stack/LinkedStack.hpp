#ifndef __LINKED_STACK_HPP
#define __LINKED_STACK_HPP
#include <stdexcept>
#include <utility>


template<typename T> 
class LinkedStack{
struct Node{
Node *next;
T data;
Node(T const &data=T(), Node *next=nullptr) : data(data), next(next) {}
};
private:

Node *m_top;

public:
void clear(){
    free();
}

operator bool() const{
    return !empty();
}

bool empty() const{
return !m_top;
}

void push(T const& data){
//same as bottom
// Node *node = Node(data);
// node->next = m_top;
// m_top = node;

//as this
m_top = new Node(data, m_top);
}

T pop(){
if(empty()){
throw std::runtime_error("empty stack");
}
T res = m_top->data;
Node *save = m_top->next;
delete m_top;
m_top = save;

return res;
}

T peek() const{
if(empty()) throw std::runtime_error("empty stack");
return m_top->data;
}

std::size_t size() const {
    Node *ptr = m_top;
    std::size_t s = 0;
    while(ptr){
        s++;
        ptr = ptr->next;
    }
    return s;
}

LinkedStack() : m_top(nullptr) {}
LinkedStack(LinkedStack const &other){
    copy(other);
}
LinkedStack(LinkedStack &&other) noexcept{
    move(std::move(other));
}

LinkedStack &operator=(LinkedStack const &other){
    if(this != &other){
    free();
    copy(other);
    }
    return *this;
}

LinkedStack &operator=(LinkedStack &&other) noexcept{
    if(this != &other){
    free();
    move(std::move(other));
    }
    return *this;
}

~LinkedStack() {free();}

private:

void copy(LinkedStack const &other){
    Node dummy;
    Node *dptr = &dummy;
    Node *optr = other.m_top;
    while (optr)
    {
        dptr->next = new Node(optr->data);
        optr = optr->next;
        dptr = dptr->next;
    }
    m_top = dummy.next;
}
void move(LinkedStack && other){
    m_top = other.m_top;
    other.m_top = nullptr;
}
void free(){
    while(!empty()){
        pop();
    }
}


};

#endif