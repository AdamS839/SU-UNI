#include <iostream>
#include <queue>
#include <stack>
#include <vector>

void reverseQ(std::queue<int> &q){
    if (q.empty()) return;
    int curr = q.front();
    q.pop();

    reverseQ(q);
    q.push(std::move(curr));
}

void reverseStack(std::queue<int> &q){
    std::stack<int> s;

    while (!q.empty()){
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()){
        q.push(s.top());
        s.pop();
    }
}

int firstUnique(std::string const &str){
    std::queue<int> q;
    int occur[256]{};

    for(int i = 0; i < str.size(); ++i){
        q.push(i);
        occur[str[i]]++;
    }

    while (!q.empty()){
        int index = q.front();
        if (occur[str[index]] == 1) return index;
        else q.pop();
    }
    return -1;
}

int main() {

    // std::queue<int> q;
    // q.push(7);
    // q.push(4);
    // q.push(5);
    // q.push(1);
    // q.push(9);
    // reverseStack(q);
    // while (!q.empty()){
    //     int curr = q.front(); q.pop();
    //     std::cout << curr << ' ';
    // }
    // std::cout << '\n';

    std::cout << firstUnique("abcd abc") << '\n'; // -> 3

    return 0;
}