#include <iostream>
#include <stack>
#include <string>

bool isOpen(const char symbol){
    return symbol == '{'
        || symbol == '['
        || symbol == '<'
        || symbol == '(';
}

bool isClose(const char symbol){
    return symbol == '}'
        || symbol == ']'
        || symbol == '>'
        || symbol == ')';
}

bool match(char open, char close){
    return open == '{' && close == '}'
        || open == '(' && close == ')'
        || open == '<' && close == '>'
        || open == '[' && close == ']';
}

bool isBalanced(std::string const &str){
    std::stack<char> stack;
    
    for (char c : str){
        if (isOpen(c)) stack.push(c);
        if (isClose(c)){
            if (stack.empty()) return false;
            if (match(stack.top(), c)){
                stack.pop();
            }
            else return false;
        }
    }
    return true;
}

int main() {

    std::string str0 = "{}";
    std::string str1 = "(a<[bcd]{}>)";
    std::string str2 = "{e&]g}";

    std::cout << std::boolalpha << isBalanced(str0) << std::endl;
    std::cout << std::boolalpha << isBalanced(str1) << std::endl;
    std::cout << std::boolalpha << isBalanced(str2) << std::endl;

    return 0;
}