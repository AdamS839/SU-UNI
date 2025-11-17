#ifndef __TestList_HPP
#define __TestList_HPP
#include <stdexcept>

template <class T>
class TestList{

public:

bool empty() const{
    return !m_begin;
}

std::size_t size() const{
    return m_size;
}

void push_front(T const &data){
    m_size++;
    Node *node = new Node(data);
    if(empty()){
        m_begin = m_end = node;
        return;
    }
    node->next = m_begin;
    m_begin = node;
}

void push_back(T const &data){
    m_size++;
    Node *node = new Node(data);
    if(empty()){
        m_begin = m_end = node;
        return;
    }
    m_end->next = node;
    m_end = node;
}

T pop_front(){
    if(empty()){
        throw std::runtime_error("empty list");
    }
    m_size--;
    T result = m_begin->data;
    Node *save = m_begin->next;
    delete m_begin;
    m_begin = save;
    if(!m_begin) m_end = nullptr;
    return result;
}

T pop_back(){
    if(empty()){
        throw std::runtime_error("empty list");
    }
    if(m_size == 1){
        pop_front();
    }
    m_size--;
    T result = m_end->data;
    Node *temp = m_begin;
    while(temp->next->next){
        temp = temp->next;
    }
    m_end = temp;
    m_end->next = nullptr;
    return result;
}

public:
static TestList<T> merge_sort(const TestList<T> &one, const TestList<T> &two);

void removeConsecutive();

void reverse();

bool isPalindrome() const;

public:

TestList(std::initializer_list<T> init) : m_begin(nullptr), m_end(nullptr), m_size(0) {
    for (const auto& item : init) {
        push_back(item);
    }
}

TestList() : m_begin(nullptr), m_end(nullptr), m_size(0) {}
TestList(TestList const &other) : TestList() {
    copy(other);
}
TestList(TestList &&other) noexcept{
    move(std::move(other));
}

TestList &operator=(TestList const &other){
    if(this != &other){
        free();
        copy(other);
    }
    return *this;
}
TestList &operator=(TestList &&other) noexcept{
    if(this != &other){
        free();
        move(std::move(other));
    }
    return *this;
}

~TestList(){
    free();
}

private:
void free(){
    Node *temp;
    while(m_begin){
        temp = m_begin->next;
        delete m_begin;
        m_begin = temp;
    }
}
void move(TestList &&other){
    m_begin = other.m_begin;
    m_end = other.m_end;
    m_size = other.m_size;
    other.m_begin = nullptr;
    other.m_end = nullptr;
    other.m_size = 0;
}
void copy(TestList const &other){
    if(other.empty()) return;

    m_size = other.m_size;
    // Node *temp = new Node(other.m_begin->data);
    // m_begin = temp;
    // Node *othertemp = other.m_begin->next;
    // while(othertemp){
    //     temp->next = new Node(other.data);
    //     temp = temp->next;
    //     othertemp = othertemp->next;
    // }
    // m_end = temp;

    Node *othertemp = other.m_begin;
    m_begin = new Node(othertemp->data);
    Node *temp = m_begin;
    othertemp = othertemp->next;

    while (othertemp) {
        temp->next = new Node(othertemp->data);
        temp = temp->next;
        othertemp = othertemp->next;
    }
    m_end = temp;
}

private:
struct Node{
    T data;
    Node *next;
    Node(T const &data, Node *next=nullptr) : data(data), next(next) {}
};

private:
Node *m_begin;
Node *m_end;
std::size_t m_size;
};

#endif