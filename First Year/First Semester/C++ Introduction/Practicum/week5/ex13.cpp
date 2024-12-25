#include <iostream>

void moveZeros(int arr[], int length){
    int counter = 0;
    for (int i = 0; i < length; i++)
    {
        if (arr[i] != 0)
        {
            arr[counter] = arr[i];
            ++counter;
        }
    }
    while (counter < length)
    {
        arr[counter] = 0;
        ++counter;
    }
}

int main() {
    int arr[50];
    int length;
    std::cin >> length;
    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
    }

    moveZeros(arr, length);
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}