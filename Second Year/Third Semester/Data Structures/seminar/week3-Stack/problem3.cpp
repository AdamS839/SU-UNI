#include <iostream>
#include <stack>

bool matching(char first, char second){
    return first == 'a' && second == 'b' || first == 'c' && second == 'd';
}

int minLength(std::string str){
    std::stack<char> stack;
    for(char c : str){
        if(stack.empty()){
            stack.push(c);
        }
        else if(matching(stack.top(), c)){
            stack.pop();
        }
        else stack.push(c);
    }
    return stack.size();
}

int main() {
    std::cout << minLength("zabaaadr") << std::endl;
    return 0;
}