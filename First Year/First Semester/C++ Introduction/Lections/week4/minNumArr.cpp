//3.1
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int arr[100];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    int smallestSoFar = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < smallestSoFar)
        {
            smallestSoFar = arr[i];
        }
    }
    std::cout << smallestSoFar << std::endl;
}