//3.3
#include <iostream>

int main() {
    int n;
    int sumOfEven = 0;
    int multiOfOdd = 1;
    std::cin >> n;
    int arr[100];

    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
        if (arr[i] % 2 == 0)
        {
            sumOfEven += arr[i];
        }
        else{
            multiOfOdd *= arr[i];
        }
    }
    std::cout << "Sum of even numbers is: " << sumOfEven << std::endl;
    std::cout << "Multiplication of odd numbers is: " << multiOfOdd << std::endl;
    
}