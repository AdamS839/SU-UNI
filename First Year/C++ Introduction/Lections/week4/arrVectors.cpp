//3.5
#include <iostream>

void VectorArr(int n){
    int vectorN = n;
    int multiVectors = 1;
    int scalar = 0;
    int arr[50];
    
    
    for (int i = 0; i < vectorN; i++)
    {
        std::cin >> arr[i];
    }
    for (int i = 0; i < vectorN; i += 2)
    {
        multiVectors = arr[i] * arr[i + 1];
        scalar += multiVectors;
    }
    
    std::cout << "Scalar product is: " << scalar << std::endl;
}

int main(){
    int n;
    std::cin >> n;
    VectorArr(n);
}