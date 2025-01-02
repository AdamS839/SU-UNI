#include <iostream>

unsigned int const length = 5;

bool SortedArr(int arr[]){
    bool sorted = false;
    for (int i = 0; i < length; i++)
    {
        if (arr[i] < arr[i + 1]) sorted = true;
        else sorted = false;
    }
    if (sorted == true) return true;
    else return false;
}

int main() {
    int arr[length];
    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
    }
    if (SortedArr(arr)){
        std::cout << "It's sorted." << std::endl;
    }
    else std::cout << "It's not sorted." << std::endl;
}