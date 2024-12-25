#include <iostream>


int binarySearch(int arr[], int length, int element){
    int high, low;
    low = 0;
    high = length -1;

    for (int i = 0; i < length; i++){
        for (int j = i + 1; j < length; j++){
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }  
        }
    }

    for (int i = 0; low <= high; i++)
    {
        int mid = (high + low) /2;
        if (arr[mid] == element)
        {
            return mid;
        }
        else if (arr[mid] < element)
        {
            low = mid + 1;
        }
        else high = mid - 1;    
    }
    return -1;
}

int main() {
    int arr[50];
    int length;
    std::cin >> length;
    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
    }
    int element;
    std::cin >> element;
    
    if (binarySearch(arr, length, element) == -1){
        std::cout<< "Element not found in array." << std::endl;
    }
    else std::cout << "Index of element you are looking for is: " << binarySearch(arr, length, element) << std::endl;

}