//3.4
#include <iostream>

void AtLeast2SameElements(int n){
    int arr[100];
    
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (arr[i] == arr[j]){
                std::cout << "At least 2 elements are the same and consecutive"<< std::endl;
                return;
            }
        }
    }
    std::cout << "Not consecutive same elements" << std::endl;
}

int main() {
    int n;
    std::cin >> n;
    AtLeast2SameElements(n);
}