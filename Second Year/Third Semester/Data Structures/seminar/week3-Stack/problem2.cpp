#include <iostream>
#include <stack>
#include <string>

bool isOpening(char c){
    return c == '(' || c == '{' || c == '<' || c == '[';
}

bool isClosing(char c){
    return c == ')' || c == '}' || c == '>' || c == ']';
}

bool matching(char open, char close){
    return open == '<' && close == '>' ||
            open == '{' && close == '}' ||
            open == '[' && close == ']' ||
            open == '(' && close == ')';
}

bool balanced(std::string str){
    std::stack<char> stack;
    for(char c : str){
        if(isOpening(c)){
            stack.push(c);
        }
        else if (isClosing(c)){
            if(stack.empty()){
                return false;
            }
            else if (matching(stack.top(), c)){
                stack.pop();
            }
            else return false;
        }
    }
    return stack.empty();
}

int main() {

    std::cout << std::boolalpha;

    std::cout << balanced("{aksmfkafs<>}") << std::endl;
    std::cout << balanced("<ajsda}") << std::endl;

    return 0;
}