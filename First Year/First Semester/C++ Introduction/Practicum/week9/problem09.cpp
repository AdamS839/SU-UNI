#include <iostream>

double divisonhelp(int arr[],int size){
    if (size <= 2)
    {
        return arr[1];
    }
    return divisonhelp(arr, size-2) / arr[size -1];
}

double division(int arr[], int size){
    if(size % 2 == 0) return divisonhelp(arr, size);
    return divisonhelp(arr, size - 1);
}

int main() {
    int arr[] = {0,8,0,4,0,4};
    std::cout << division(arr,6) << std::endl;

    return 0;
}