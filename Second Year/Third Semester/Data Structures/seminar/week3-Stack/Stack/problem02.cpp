#include "LinkedStack.hpp"
#include <iostream>
#include <string>

bool isOpening(char c){
    return c == '(' || c =='['  || c == '{'  || c == '<' ;
}

bool isClosing(char c){
    return c == ')'|| c == ']'|| c == '}'|| c == '>';
}

bool match(char open, char close){
    return open=='(' && close == ')'
    || open == '{' && close == '}'
    || open == '[' && close == ']'
    || open == '<' && close == '>';
}

bool balanced(std::string const &s){
    LinkedStack<char> stack;
    for(char c : s){
        if(isOpening(c)){
            stack.push(c);
        }
        else if(isClosing(c)){
            if(stack.empty()){
                return false;
            }
            else if(match(stack.peek(), c)){
                stack.pop();
            }
            else return false;
        }
    }
    return stack.empty();
}

int main(){

    std::cout << std::boolalpha << balanced("()") << std::endl;
    std::cout << std::boolalpha << balanced("(a<[bcd]{}>)") << std::endl;
    std::cout << std::boolalpha << balanced("{e&]g}") << std::endl;

    return 0;
}