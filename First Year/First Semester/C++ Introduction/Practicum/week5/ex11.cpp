#include <iostream>

void insertionSort(int arr[], int length){
    for (int i = 1; i < length; i++)
    {
        int dot = arr[i];
        int j = i - 1;
        while( j >= 0 && arr[j] > dot){
            arr[j+1] = arr[j];
            --j;
        }
        arr[j + 1] = dot;
    }
    
}

void MergeArrays(int arr1[], int arr2[], int length1, int length2, int mergedArr[]){
    int i = 0, j = 0, k = 0;
    while (i < length1 && j < length2)
    {
        if (arr1[i] < arr2[j]){
            mergedArr[k] = arr1[i];
            ++i;
        }
        else {
            mergedArr[k] = arr2[j];
            ++j;
        }
        ++k;
    }
    while (i < length1)
    {
        mergedArr[k] = arr1[i];
        ++i;
        ++k;
    }
    while (j < length2)
    {
        mergedArr[k] = arr2[j];
        ++j;
        ++k;
    }
    
    std::cout << "Merged array: ";
    for (int i = 0; i < length1 + length2; i++)
    {
        std::cout << mergedArr[i] << " ";
    }
    std::cout << std::endl;
    
}

int main() {
    int arr1[50];
    int arr2[50];
    int lengthFirst, lengthSecond;
    
    std::cout << "Length of first array: ";
    std::cin >> lengthFirst;

    std::cout << "Length of second array: ";
    std::cin >> lengthSecond;

    for (int i = 0; i < lengthFirst; i++)
    {
        std::cin >> arr1[i];
    }
    for (int i = 0; i < lengthSecond; i++)
    {
        std::cin >> arr2[i];
    }

    insertionSort(arr1, lengthFirst);
    insertionSort(arr2, lengthSecond);

    int mergedArr[lengthFirst + lengthSecond];
    MergeArrays(arr1, arr2, lengthFirst, lengthSecond, mergedArr);

}