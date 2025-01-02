#include <iostream>

int biggestGrowingArrLength(int arr[], int length){
    if (length == 0) return 0;
    int counter = 0;
    int maxLength = 0;
    for (int i = 1; i < length; i++){
        if (arr[i - 1] < arr[i]){
            ++counter;
        }
        else {
            if (maxLength < counter){
                maxLength = counter;
            }
            counter = 0;
        } 
    }

    if(maxLength < counter){
        maxLength = counter;
    }
    return maxLength;
}

int main() {
    int arr[50];
    int length;
    std::cin >> length;
    for (int i = 0; i < length; i++)
    {
        std::cin >> arr[i];
    }
    
    std::cout << biggestGrowingArrLength(arr, length) << std::endl;

}