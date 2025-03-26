#include <iostream>

template<class T>
struct Nodes{
    T data;
    Nodes *next;
    Nodes(const T val) : data(val), next(nullptr) {}

};

template <class T>
class LinkedList{
    Nodes<T> *first = nullptr;
    Nodes<T> *end = nullptr;
public:
    bool empty(){
        return !first;
    }

    void push_forward(const T& val){
        Nodes<T>* newval = new Nodes<T>(val);
        newval->next = first;
        first = newval;
        if (!end) end = first;
    }

    void push_back(const T& val){
        Nodes<T> *newval = new Nodes<T>(val);
        if (!first) {
            first = end = newval;
            return;
        }
        end->next = newval;
        end = newval;
    }

    void removeFirst() const{
        // Nodes<T> *temp = first;
        // delete[] first;
        // first = temp->next;


        // DO LATER CMON MAN
        if (!first) return;
        Nodes<T>* temp = first;
        first = first->next;
        delete temp;
        if (!first) end = nullptr;
    }

    void removeEnd() const{
        Nodes<T> *temp = first;
        while(temp && temp->next && temp->next->next){
            temp = temp->next;
        }
        delete[] temp->next;
        temp = nullptr;
    }

    void addElementByIndex(const T& value, std::size_t index){
        if(index <0) throw std::invalid_argument("invalid index");

        if(index == 0) {
            push_forward(value);
            return;
        }

        Nodes<T> *newVal = new Nodes<T>[value];
        Nodes<T> *current = first;
        
        std::size_t i = 0;
        
        while (current && i < index - 1)
        {
            current = current->next;
            ++i;
        }

        if(!current){
            delete[] newVal;
            throw std::invalid_argument("Outside bounds");
        }

        newVal->next = current->next;
        current->next = newVal;
        

        if(!newVal->next){
            end = newVal;
        }
    }

    void removeElementByIndex(const T& value, std::size_t index){
        
    }

    void print() const{
        Nodes<T>* temp = first;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr\n";
    }

    void reverseList(){

    }

};
