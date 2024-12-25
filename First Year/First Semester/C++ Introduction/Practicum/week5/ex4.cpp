#include <iostream>

unsigned int const length = 5;

void printReversedElements(int arr[]){
    for (int i = length-1; i >= 0; i--)
    {
        int temp = arr[i];
        arr[i] = arr[length -1 - i];
        arr[i] = temp;
        std::cout<< arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[length];
    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
    }
    printReversedElements(arr);
}