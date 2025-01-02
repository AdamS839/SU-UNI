#include <iostream>

unsigned int const length = 5;

double Average(double arr[]){
    double sum = 0;
    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
        sum += arr[i];
    }
    return (sum / length);
}

void printArr(double arr[]){
    std::cout << std::endl;
    for (int i = 0; i < length; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    double arr[length];
    std::cout << Average(arr);
    printArr(arr);
}