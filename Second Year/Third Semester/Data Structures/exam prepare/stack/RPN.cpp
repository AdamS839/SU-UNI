#include <iostream>
#include <stack>
#include <string>
#include <cmath>

bool isOperation(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

double eval(char op, double lhs, double rhs){
    switch (op){
    case '+': return lhs + rhs;
    case '-': return lhs - rhs;
    case '*': return lhs * rhs;
    case '/': return lhs / rhs;
    case '^': return std::pow(lhs, rhs);
    default:
        throw std::runtime_error("Error");
    }
}

int evalRPN(std::string const &str){
    std::stack<double> stack;

    for (char c : str){
        if (std::isdigit(c)){
            stack.push(c - '0');
        }
        else if (isOperation(c)){
            double rhs = stack.top();
            stack.pop();
            double lhs = stack.top();
            stack.pop();

            stack.push(eval(c, lhs, rhs));
        }
        else throw std::runtime_error("Invalid symbol");
    }
    if (stack.empty()) throw std::runtime_error("invalid expr");
    double result = stack.top();
    stack.pop();
    if(!stack.empty()) throw std::runtime_error("too many nums in expre");
    return result;
}

// toRPN


int main() {

    std::cout << evalRPN("123*+") << std::endl;

    return 0;
}