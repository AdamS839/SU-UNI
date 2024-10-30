//3.5
#include <iostream>

bool isArrMonotnicallyGrowing(int n){
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    std::cin >> n;
    if (isArrMonotnicallyGrowing(n)){
        std::cout << "Monotonically Growing" << std::endl;
    }
    else std::cout << "Not monotonically growing" << std::endl;
}