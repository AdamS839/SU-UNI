#include <iostream>

void print(int arr[], bool subset[], int size){
    for (int i = 0; i < size; i++)
    {
        if (subset[1]) std::cout << arr[i];
    }
    std::cout << std::endl;
}

void subsets(int arr[], int index, int size, bool subset[]){
    print(arr, subset, size);
    for (int i = index; i < size; i++)
    {
        subset[i] = true;
        subsets(arr, i + 1, size, subset);
        subset[i] = false;
    }
    
}

int main() {
    
    int arr[3] = {1,2,3};
    bool subset[3] {};
    subsets(arr, 3 ,0, subset);
    return 0;
}