#include <iostream>

int const size = 4;

void product(int arr[size], int prodArr[size]){
    for (int i = 0; i < size; i++){
        prodArr[i] = 1;
        for (int j = 0; j < size; j++){
            if (j != i){
                prodArr[i] *= arr[j];
            } 
        }
    }
}

int main() {
    int arr[size] = {1,2,3,4};
    int prodarr[size];
    product(arr, prodarr);
    for (int i = 0; i < size; i++)
    {
        std::cout << prodarr[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}