#include <iostream>

void swap1(int* a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int *begin, int *end){
    if (begin > end) return;
    swap1(begin, end);
    reverse(begin+1,end-1);
}

int main() {
    int arr[] = {1,2,3,4,5};
    reverse(arr, arr+4);
    for (int i = 0; i < 5; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}