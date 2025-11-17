#include "LinkedStack.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

bool isOperator(char c){
    return c == '+' || c == '-' || c=='/' || c=='*' || c=='^';
}

double eval(double lhs, double rhs, char op){
    switch (op)
    {
    case '+': return lhs + rhs;
    case '-': return lhs - rhs;
    case '/': return lhs / rhs;
    case '*': return lhs * rhs;
    case '^': return std::pow(lhs, rhs);
    default:
        throw std::runtime_error("not enough args");
    }
}

std::string toRPN(std::string const &s){
    LinkedStack<double> nums;

    for(char c : s){
        if(isdigit(c)){
            nums.push(c-'0');
        }
        else if (isOperator(c)){
            try{
                double lhs, rhs;
                rhs = nums.pop();
                lhs = nums.pop();
            }
            catch (...){
                throw std::runtime_error("not enough numbers");
            }
        }
        else{
            throw std::runtime_error("invalid symbol");
        }
    }
}

int main(){

    return 0;
}