#include <iostream>

template<class T>
struct Pair{
T a, b;
};

template<class T>
void printPair(Pair<T> p){
    std::cout << '(' << p.a << ',' << p.b << ')';
}

// template<class T>
// void addPair(){
//     T a, b;
//     std::cin >> a >> b;
// }

template<class T>
T sumPair(Pair<T> &p1, Pair<T> &p2){
    Pair<T> p3;
    p3.a = p1.a + p2.a;
    p3.b = p1.b + p2.b;
    return p3;
}

template<class T>
void reversePair(Pair<T> &pair){
    T temp = pair.a;
    pair.a = pair.b;
    pair.b = temp;
}

template<class T>
void compare(Pair<T> &p1, Pair<T> &p2){
    if(p1.a == p2.a && p1.b == p2.b)
    if(p1.a < p2.a || p1.a == p2.a && p1.b < p2.b)
    if(p1.a > p2.a || p1.a == p2.a && p1.b > p2.b)
}

int main() {
    Pair<int> p1 = {1,2};
    Pair<int> p2 = {5,2};
    
    //reversePair(p1);
    //printPair(p1);

    compare(p1,p2);

    return 0;
}