#include <iostream>

template<class T>
T biggerNum(T a, T b){
    return (a > b) ? a:b;
}

template<>
float biggerNum(float a, float b){
    return (a - b) > __FLT_EPSILON__ ? a : b;
}

template<>
double biggerNum(double a, double b){
    return (a-b) > __DBL_EPSILON__ ? a : b;
}

int main() {

    std::cout << biggerNum<int>(120, 119) << std::endl;
    std::cout << biggerNum<double>(0.299999998,0.299999999) << std::endl;
    std::cout << biggerNum<float>(0.399999, .4) << std::endl;

    return 0;
}