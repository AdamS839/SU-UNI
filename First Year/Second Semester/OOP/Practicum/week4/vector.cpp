#include <iostream>

template<class T>
class Vector{
private:
    T* data;
    std::size_t size;
    std::size_t capacity;
public:
    Vector():size(0), capacity(0) {};

    Vector(Vector& other): size(other.size), capacity(other.capacity){
        //delete[] data;
        data = new T[capacity];
        for (std::size_t i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    Vector& operator=(Vector const& other){
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (std::size_t i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
        return *this;
    }

    ~Vector(){
        delete[] data;
    }

    Vector(std::size_t capacity, T const& initEl=T()){
        this->size = size;
        this->capacity = capacity;
        data = new T[capacity];
        for (std::size_t i = 0; i < size; ++i)
        {
            data[i] = initEl;
        }
    }

    // Vector(std::initializer_list<T> const& l){

    // }

    void push(T const& value){
        if(size < capacity){
            data[size] = value;
            ++size;
        }
        else return;
    }

    void insert(std::size_t index, T const& value){
        if(index > size) return;
        if(size == capacity){
            if(capacity == 0){
                capacity = 1;
            }
            else capacity *= 2;
            T *newData = new T[capacity];
            for (std::size_t i = 0; i < size; ++i)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        for (std::size_t i = size; i > index; ++i)
        {
            data[i] = date[i-1];
        }
        data[index] = value;
        ++size;
    }

    bool empty() const{
        return size == 0;
    }

    std::size_t getSize() const{
        return this->size;
    }

    std::size_t getCapacity() const{
        return this->capacity;
    }

    void removeLast(){
        if(size > 0) --size;
        else return;
    }

    void removeByIndex(int index){
        if(index > size){
            return;
        }
        for (int i = index; i < size - 1; ++i)
        {
            data[i] = data[i+1];
        }
        --size;
    }

    T& operator[](int index){
        if(index > size){ return -1; }
        return data[index];
    }

    void clear(){
        size = 0;
    }

    void swap(Vector& other){
        std::swap(this->data, other.data);
        std::swap(this->size, other.size);
        std::swap(this->capacity, other.capacity);
    }
};

int main() {

    return 0;
}