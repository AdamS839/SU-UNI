#include <iostream>

int const size = 5;

void changeArr(int arr[]){
    for (int i = 0; i < size - 1; i+=2)
    {
        int maxindex = i;
        int minindex = i;
        for (int j = i; j < size; j++)
        {
            if(arr[j] > arr[maxindex]) maxindex = j;
            if(arr[j] < arr[minindex]) minindex = j;
        }
        std::swap(arr[i], arr[maxindex]);
        std::swap(arr[i+1], arr[minindex]);
    }
}

int main() {
    int arr[size] = {1,9,2,8,3};
    int arr1[size] = {5,3,7,1,4};

    changeArr(arr1);
    for (int i = 0; i < size; i++)
    {
        std::cout << arr1[i] << ' ';
    }
    std::cout << std::endl;
    
    return 0;
}