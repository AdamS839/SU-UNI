#include "list.h"

template<class T>
List<T>::List():first(nullptr) {}


// 12.2
template<class T>
List<T>::List(int x, int y) : first(nullptr){
    if(x > y){
        throw std::invalid_argument("Wrong interval");
    }
    first = new box<T>{x, nullptr};
    box<T> *current = first;
    for (int i = x+1;  i < y;  ++i)
    {
        current->next = new box<T>[i, nullptr];
        current = current->next;
    }
}

template<class T>
void List<T>::clear(){
    box<T> *current = first;
    while (first != nullptr)
    {
        current = first->next;
        delete first;
        first = current;
    }
    first = nullptr;
}

// 12.14
template<class T>
List<T>::~List(){
    clear();
}

template<class T>
List<T>::List(const List<T> &other){
    copyFrom(other.first);
}


template<class T>
void List<T>::copyFrom(box<T> *other){
    box<T> *current = other;
    box<T> *prevCreated = nullptr;
    box<T> *newCreated = nullptr;

    while (current != nullptr)
    {
        newCreated = new box<T>{current->data, nullptr};
        if (prevCreated == nullptr)
        {
            first = newCreated;
        }
        else {
            prevCreated->next = newCreated;
        }
        prevCreated = newCreated;

        //prevCreated = prevCreated->next = new box<T>{current->data, nullptr};

        current = current->next;
    }
}

template<class T>
List<T>& List<T>::operator=(const List<T>& other){
    if(&other != this){
        clear();
        copyFrom(other.first);
    }
}

template<class T>
bool List<T>::empty() const{
    return first == nullptr;
}

template<class T>
unsigned List<T>::count() const{
    unsigned c = 0;
    box<T> *current = first;
    while (current != nullptr)
    {
        ++c;
        current = current->next;
    }
    return c;
}

template<class T>
T& List<T>::operator[](unsigned i){
    box<T> *current = pointerTo(i);
    if(current == nullptr){
        throw std::invalid_argument("Out of bounds");
    }
    return current->data;
}

// 12.4
template<class T>
List<T>& List<T>::operator+=(T x){
    push_back(x);
    return *this;
}

template<class T>
box<T> *List<T>::pointerTo(unsigned i){
    unsigned c = 0;
    box<T> *current = first;
    while (current != nullptr && c < i)
    {
        ++c;
        current = current->next;
    }
    return current;
}

template<class T>
void List<T>::insertAfter(T x, unsigned i){
    box<T> *current = pointerTo(i);
    if(current == nullptr){
        throw std::invalid_argument("Out of bounds");
    }
    current->next = new box<T>{x,current->next};
}

template<class T>
void List<T>::push(T x){
    //std::cout << "test" << std::endl;
    box<T> *newBox = new box<T>{x, nullptr};
    newBox->next = first;
    first = newBox;
}

// 12.3
template<class T>
void List<T>::push_back(T x){
    box<T> *newOne = new box<T>{x, nullptr};
    if(first == nullptr){
        first = newOne;
        return;
    }
    box<T> *temp = first;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next= newOne;
}

template<class T>
void List<T>::append(const List<T> &other){
    if(other.first == nullptr) return;

    box<T> *currentOther = other.first;
    while (currentOther != nullptr)
    {
        push_back(currentOther->data);
        currentOther = currentOther->next;
    }
}

template<class T>
void List<T>::print() const{
    //std::cout << "test" << std::endl;
    box<T> *temp = first;
    while (temp != nullptr)
    {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << "nullptr" << std::endl;
}

template<class T>
bool List<T>::operator==(const List<T> &other) const{
    if(count() != other.count()) return false;

    box<T> *curr = first;
    box<T> *currOther = other.first;

    while (curr != nullptr)
    {
        if(curr->data != currOther->data) return false;
        curr = curr->next;
        currOther = currOther->next;
    }
    return true;
}