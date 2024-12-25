#include <iostream>

int find(int arr[], int length, int elementToFind){
    for (int i = 0; i < length; i++)
    {
        if (elementToFind == arr[i])
        {
            return i;
        }
    }
    return -1;
}

int rfind(int arr[], int length, int elementToFind){
    for (int i = length - 1; i >= 0; i--)
    {
        if (elementToFind == arr[i])
        {
            return i;
        }
    }
    return -1;
}

int main() {
    int arr[50];
    int length;
    int elementToFind;
    std::cin >> length;
    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
    }

    std::cout << "Input element from array: ";
    std::cin >> elementToFind;

    std::cout << "The index of the first met element: "<< find(arr, length, elementToFind) << std::endl;
    std::cout << "The index of the last met element: "<< rfind(arr, length, elementToFind) << std::endl;
}