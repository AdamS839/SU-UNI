#include <iostream>
#include "Stack/LinkedStack.hpp"
#include <string>
#include <cmath>
#include <vector>

double applyOp(char op, double lhs, double rhs){
    switch (op)
    {
    case '+': return lhs + rhs;
    case '-': return lhs - rhs;
    case '*': return lhs * rhs;
    case '/': return lhs / rhs;
    case '^': return pow(lhs, rhs);
    default:
        throw std::runtime_error("Invalid operation symbol");
    }
}

bool isOperation(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int priority(char op){
    switch (op)
    {
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    case '^': return 3;
    default:
        throw std::runtime_error("unrecognised operation");
    }
}

double evalRPN(std::string const &expr){
    LinkedStack<double> nums;

    for (char c : expr){
        if(std::isdigit(c)){
            nums.push(c - '0');
        }
        else if (isOperation(c)){
            double lhs, rhs;
            try{
                rhs = nums.pop();
                lhs = nums.pop();
            }
            catch (...){
                throw std::runtime_error("not enough args");
            }
            nums.push(applyOp(c, lhs, rhs));
        }
        else{
            throw std::runtime_error("Invalid symbol");
        }
    }

    if(nums.empty()) throw std::runtime_error("invalid expression");
    double result = nums.peek();
    nums.pop();
    if(!nums.empty()){
        throw std::runtime_error("too many nums in expression");
    }
    return result;
}

std::string toRPN(std::string const &expr){
    LinkedStack<char> ops;
    std::string result;

    for(char c : expr){
        if(std::isdigit(c)){
            result += c;
        }
        else if (c == '('){
            ops.push(c);
        }
        else if(c == ')'){
            while(ops && ops.peek() != '('){
                result += ops.peek();
                ops.pop();
            }
            if(!ops){
                throw std::runtime_error("no opening parenthesis found");
            }
            ops.pop();
        }
        else if(isOperation(c)){
            int cp = priority(c);
            while(ops && ops.peek() != '(' && cp <= priority(ops.peek())){
                result += ops.peek();
                ops.pop();
            }
            ops.push(c);
        }
        else throw std::runtime_error("Invalid symbol");
    }

    while(ops){
        if(ops.peek() == '(') throw std::runtime_error("patenthesis was never closed");
        result += ops.peek();
        ops.pop();
    }

    return result;
}

double evalFastRPN(std::vector<std::string> const &expr){
    LinkedStack<double> stack;
    for (auto &s : expr){
        if(s == "+" || s == "-" || s == "*" || s == "/" || s == "^"){
            double rhs = stack.pop();
            double lhs = stack.pop();

            if(s == "+") stack.push(lhs + rhs);
            else if (s == "-") stack.push(lhs - rhs);
            else if (s == "*") stack.push(lhs * rhs);
            else if (s == "/") stack.push(lhs / rhs);
            else if (s == "^") stack.push(pow(lhs, rhs));
        }
        else {
            stack.push(std::stod(s));
        }
    }
    double res = stack.pop();
    if(!stack.empty()) throw std::runtime_error("Not empty stack");

    return res;
}


int main() {
    //std::cout << toRPN("1+2*3") << " = " << evalRPN(toRPN("1+2*3")) << std::endl;
    // std::string expr = toRPN("2+2*4/8+3^2");
    std::string expr = toRPN("1+4-5*3+2^0+9");

    //std::vector<std::string> exp {"2","2","4","*","8","/","+","3","2","^","+"};

    std::cout << expr << " = " << evalRPN(expr) << std::endl;

    return 0;
}
