#include <iostream>

unsigned int const length = 5;

void MaxElement(int arr[]){
    int Max = arr[0];

    for (int i = 0; i < length; i++)
    {
        if (Max < arr[i]){
            Max = arr[i];
        }
    }
    std::cout<< "Max element: " << Max << std::endl;
    
}

void MinElement(int arr[]){
    int Min = arr[0];
    for (int i = 0; i < length; i++)
    {
        if (Min > arr[i]){
            Min = arr[i];
        }
    }
    std::cout<< "Min element: " << Min << std::endl;
    
}

int main() {
    int arr[length];
    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
    }
    /*
    int maxElement = arr[0];
    int minElement = arr[0];
    for (int i = 0; i < length; i++){
        if (maxElement < arr[i]){
            maxElement = arr[i];
        }
        else if (minElement < arr[i]){
            minElement = arr[i];
        }
    }*/
    //std::cout << "Max element is: " << maxElement <<std::endl;
    //std::cout << "Min element is: " << minElement <<std::endl;

    MinElement(arr);
    MaxElement(arr);
}