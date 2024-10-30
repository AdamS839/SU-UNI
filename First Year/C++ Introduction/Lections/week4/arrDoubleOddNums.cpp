//3.2
#include <iostream>

int main() {
    int n;
    int sumOfDoubledOdd = 0;
    std::cin >> n;

    int arr[100];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
        if ((arr[i] / 2) % 3 == 0 && arr[i] > 1)
        {
            sumOfDoubledOdd += arr[i];
        }
    }
    std::cout << sumOfDoubledOdd << std::endl;
    
}