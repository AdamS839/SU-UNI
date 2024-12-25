#include <iostream>

void generateVectors(int n, int i, int arr[]){
    if (i == n) {
        for (int i = 0; i < n; i++)
        {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
        return;
    }
    arr[i] = 0;
    generateVectors(n, i+1, arr);
    arr[i] = 1;
    generateVectors(n, i+1, arr);

}

int main() {
    int n;
    std::cin >> n;
    int arr[255];
    generateVectors(n, 0, arr);
    return 0;
}