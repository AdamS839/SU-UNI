#include <iostream>
#include <stack>
#include <vector>

bool matching(char open, char close){
    return open == '(' && close == ')'
        || open == '[' && close == ']'
        || open == '<' && close == '>'
        || open == '{' && close == '}';
}

bool isOpen(char c){
    return c == '(' || c == '[' || c == '<' || c == '{';
}

bool isClose(char c){
    return c == ')' || c == '}' || c == ']' || c == '>';
}

bool isBalanceBracket(std::string const &str){
    std::stack<char> stack;
    for (char c : str){
        if (isOpen(c)) stack.push(c);
        else if (isClose(c)){
            if (stack.empty()) return false;
            else if (matching(stack.top(), c)) stack.pop();
            else return false;
        }
    }
    return stack.empty();
}


bool matchLetters(char open, char close){
    return open == 'a' && close == 'b' || open == 'c' && close == 'd';
}

int minLength(std::string const &str){
    std::stack<char> stack;
    for (char c : str){
        if (stack.empty()) stack.push(c);
        else if (matchLetters(stack.top(), c)) stack.pop();
        else stack.push(c);
    }
    return stack.size();
}

bool subsetSum(std::vector<int> const &vec, int target){
    std::stack<std::pair<int,int>> stack;
    stack.push({target, 0});
    while(!stack.empty()){
        auto [res, ind] = stack.top();
        stack.pop();

        if(res == 0) return true;
        if(ind >= vec.size()) continue;

        stack.push({res - vec[ind], ind + 1});
        stack.push({res, ind+1});
    }
    return false;
}

int main() {
    std::cout << std::boolalpha;

    // std::cout << isBalanceBracket("{}") << '\n';
    // std::cout << isBalanceBracket("(a<[bcd]{}>)") << '\n';
    // std::cout << isBalanceBracket("{e&]g}") << '\n';

    // std::cout << minLength("aabacd") << '\n';
    // std::cout << minLength("aabbcd") << '\n';

    std::cout << subsetSum({1,2,3,4}, 5) << '\n'; // ~> true
    std::cout << subsetSum({1,4,5,6}, 13) << '\n'; // ~> false

    return 0;
}