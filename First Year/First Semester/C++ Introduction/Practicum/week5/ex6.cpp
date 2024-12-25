#include <iostream>

void bubbleSortAsc(int arr[], int length){
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout<< std::endl;
    
}

void bubbleSortDesc(int arr[], int length){
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (arr[i] < arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout<< std::endl;
}

void selectionAsc(int arr[], int length){
    for (int i = 0; i < length; i++)
    {
        int index = i;
        for (int j = i + 1; j < length; j++)
        {
            if (arr[j] < arr[index])
            {
                index = j;
            }
            int temp = arr[i];
            arr[i] = arr[index];
            arr[index] = temp;
        }
    }
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout<< std::endl;
}

int main() {
    int arr[100];
    int length;
    std::cin>> length;

    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
    }

    //bubbleSortAsc(arr);
    //bubbleSortDesc(arr);
    selectionAsc(arr, length);
}