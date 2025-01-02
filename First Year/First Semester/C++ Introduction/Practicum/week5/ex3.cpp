#include <iostream>

unsigned int const length = 5;

void RemoveIndex(int arr[], int removeindex){
    for (int i = removeindex; i < length; i++)
    {
        arr[i] = arr[i + 1];
    }
    for (int i = 0; i < length - 1; i++)
    {
        std::cout << arr[i] << " ";
    }
    
}

int main() {
    int arr[length];
    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
    }
    int removeIndex;
    std::cout << "Index to be removed: ";
    std::cin >> removeIndex;

    RemoveIndex(arr, removeIndex);
    
}