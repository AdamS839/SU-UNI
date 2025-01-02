#include <iostream>

const int length = 5;

int arrDiff(int arr[], int size, int index){
    if (index >= size - 1) 
    {
        return arr[index];
    }
    return arrDiff(arr,size,index + 1) - arr[index];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::cout << arrDiff(arr, length, 0) << std::endl;
}