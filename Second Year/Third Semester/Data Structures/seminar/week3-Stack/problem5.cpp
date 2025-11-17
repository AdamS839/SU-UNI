#include <iostream>
#include <stack>
#include <vector>

bool subsetSum(std::vector<int> const &vec, int target){
    std::stack<std::pair<int, int>> stack;
    stack.push({target, 0});
    while(!stack.empty()){
        auto[res, idx] = stack.top();
        stack.pop();
        if(res == 0) return true;
        if(idx >= vec.size()) continue;

        stack.push({res - vec[idx], idx+1});
        stack.push({res, idx+1});
    }
    return false;
}

int main() {
    std::cout << std::boolalpha;
    std::cout << subsetSum({1,2,3,4}, 5) << std::endl;
    std::cout << subsetSum({1,4,5,6}, 13) << std::endl;
    return 0;
}