#ifndef _ObjectSet_H
#define _ObjectSet_H
#include <iostream>
#include <vector>

class Set{
public:
Set() {}
virtual ~Set() {}
virtual bool member(int x) const = 0;
};

class EvenSet : public Set{
public:
bool member(int x) const{
    return x % 2 == 0;
}
};

class DynamicSet : public Set{
int *arr;
int capacity;
int size;
public:
DynamicSet(int cap) : capacity(cap), size(0), arr(new int[capacity]) {}
~DynamicSet(){delete arr;} 

void addElement(int x){
    if(size < capacity){
        arr[size++] = x;
    }
}
bool member(int x) const{
    for (int i = 0; i < size; ++i)
    {
        if(arr[i] == x) return true;
    }
    return false;
}
};

class UnionSet : public Set{
std::vector<Set*> sets;
public:
void addSet(Set* set){
    sets.push_back(set);
}
bool member(int x) const{
    for(Set* s : sets){
        if(s->member(x)) return true;
    }
    return false;
}

};

#endif