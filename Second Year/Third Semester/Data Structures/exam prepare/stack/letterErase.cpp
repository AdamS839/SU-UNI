#include <iostream>
#include <stack>
#include <string>

bool isOpen(char symbol){
    return symbol == 'a' || symbol == 'c';
}

bool isClose(char symbol){
    return symbol == 'b' || symbol == 'd';
}

bool match(char open, char close){
    return open == 'a' && close == 'b' || open == 'c' && close == 'd';
}

int minLength(std::string const &str){
    std::stack<char> stack;

    for (char c : str){
        if(stack.empty()) stack.push(c);
        else if (match(stack.top(), c)) stack.pop();
             else stack.push(c);
    }

    return stack.size();
}

int main() {

    std::string str0 = "aabacd";
    std::string str1 = "aabbcd";
    std::cout << minLength(str0) << std::endl;
    std::cout << minLength(str1) << std::endl;

    return 0;
}