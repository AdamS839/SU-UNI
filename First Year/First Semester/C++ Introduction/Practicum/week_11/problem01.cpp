#include <iostream>

void swap1(int* a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap2(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int a = 10;
    int b = 5;
    
    swap2(a,b);
    return 0;
}