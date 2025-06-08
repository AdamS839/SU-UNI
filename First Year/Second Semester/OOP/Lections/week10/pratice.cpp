#include <iostream>
#include <functional>
#include <vector>

class Set
{
public:
Set() {};
virtual ~Set() {};
virtual bool member(int x) const = 0;
};

class EmptySet : public Set
{
public:
bool member(int x) const {
    return false;
}
};

class EvenSet : public Set
{
public:
bool member(int x) const{
    return x % 2 == 0;
}
};

class ArraySet : public Set
{
private:
int *data;
int size;
int capacity;
public:
ArraySet(int capacity) : capacity(capacity), data(new int[capacity]), size(0) {}
~ArraySet(){ delete[] data;}

void push_back(int x){
    if(size < capacity){
        data[size++] = x;
    }
}

bool member(int x) const{
    for(int i = 0; i < size; ++i){
        if(data[i] == x){
            return true;
        }
    }
    return false;
}
};

class TruthSet : public Set
{
private:
std::function<bool(int)> f;
public:
TruthSet(std::function<bool(int)> func) : f(func) {}
bool member(int x) const{
    return f(x);
}
};

class SetIntersection : public Set
{
std::vector<Set*> sets;
public:
SetIntersection() {}
void add(Set* set){
    sets.push_back(set);
}
bool member(int x) const{
    for(const Set* set : sets){
        if(!set->member(x)) return false;
    }
    return true;
}
};

bool test(std::vector<Set*> sets, int x){
    for(const Set* set : sets){
        if(!set->member(x)) return false;
    }
    return true;
}

int main() {

//---------------------------------------//

// EmptySet set0;
// std::cout << set0.member(100) << std::endl;

// EvenSet setTimes2;
// std::cout << setTimes2.member(46) << std::endl;
// std::cout << setTimes2.member(47) << std::endl;

// ArraySet arrSet(10);
// arrSet.push_back(10);
// arrSet.push_back(20);
// arrSet.push_back(30);
// arrSet.push_back(40);
// arrSet.push_back(50);
// arrSet.push_back(60);
// std::cout << arrSet.member(10) << std::endl;
// std::cout << arrSet.member(100) << std::endl;

//---------------------------------------//

// // Test function

// std::vector<Set*> sets;
// Set* setzero = new EmptySet();
// Set* set2 = new EvenSet();
// ArraySet* setarr = new ArraySet(10);
// TruthSet* tfset = new TruthSet([](int x) -> bool {return x > 20;});

// setarr->push_back(10);
// setarr->push_back(20);
// setarr->push_back(30);
// setarr->push_back(46);

// sets.push_back(setzero);
// sets.push_back(set2);
// sets.push_back(setarr);
// sets.push_back(tfset);

// std::cout << "is X inside: " << test(sets, 46) << std::endl;

//---------------------------------------//


SetIntersection* inters = new SetIntersection();    
Set* set2 = new EvenSet();

// Intersection Set
// inters->add(set2);
// std::cout << inters->member(2) << std::endl;

//---------------------------------------//

Set* setzero = new EmptySet();
ArraySet* arrset = new ArraySet(10);
arrset->push_back(10);
arrset->push_back(20);
arrset->push_back(30);

// Intersection set within another intersection set

SetIntersection* intinter = new SetIntersection();

inters->add(set2);
inters->add(intinter);
//intinter->add(setzero);
intinter->add(arrset);
std::cout << inters->member(30) << std::endl;

//---------------------------------------//

}