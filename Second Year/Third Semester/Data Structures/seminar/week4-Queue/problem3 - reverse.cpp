#include <iostream>
#include <queue>
/*
template<class T>
void reverseStack(){

    while(!s.empty()){
        q.push(s.top());
        s.pop();
    }
}
*/

template<class T>
void reverseRec(std::queue<T> &q){
    if(q.emplace()) return;
    T temp = q.front();
    q.pop();
    reverseRec(q);
    q.push(temp);
}


int main() {

    

    return 0;
}