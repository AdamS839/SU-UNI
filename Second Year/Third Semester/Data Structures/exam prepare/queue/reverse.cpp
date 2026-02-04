#include <iostream>
#include <queue>


template<typename T>
void reverseRec(std::queue<T> &q){
    if (q.empty()) return;
    T temp = q.front();
    q.pop();

    reverseRec(q);
    q.push(std::move(temp));
}

int main() {

    std::queue<int> q;
    q.push(1); q.push(2); q.push(3);

    reverseRec(q);

    while (!q.empty()){
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;


    return 0;
}