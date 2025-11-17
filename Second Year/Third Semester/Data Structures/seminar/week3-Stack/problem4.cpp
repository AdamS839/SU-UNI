#include <iostream>
#include <stack>
#include <vector>

template<typename T, typename F>
F foldr(F(*op)(T,F), F nv, std::vector<T> const &v){
    std::stack<T> stack;
    for (T el : v){stack.push(el);}
    while(!stack.empty()){
        nv = op(stack.top(), nv);
        stack.pop();
    }
    return nv;
}

int main() {

    std::cout << foldr<int, int>([](int x, int y) { return x*y; }, 1, {1,2,3,4,5}) << std::endl;

    return 0;
}