#include <iostream>
#include <vector>
#include <stack>

bool subsetSum(std::vector<int> const &vec, int target){
    std::stack<std::pair<int, int>> stack;

    stack.push({target, 0});
    while(!stack.empty()){
        auto [res, ind] = stack.top();
        stack.pop();
        if(res == 0) return true;
        if (ind >= vec.size()) continue;
        stack.push({res - vec[ind], ind + 1});
        stack.push({res , ind + 1}); 
    }

    return false;
}


int main() {

    std::cout << std::boolalpha;

    std::cout << subsetSum({1,2,3,4}, 5) << std::endl;

    std::cout << subsetSum({1,4,5,6}, 13) << std::endl;

    return 0;
}