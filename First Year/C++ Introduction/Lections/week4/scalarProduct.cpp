//3.6
#include <iostream>

void ScalarProduct(int n){
    int arrA[n], arrB[n];
    int product = 1;
    int scalarProduct = 0;
    for (int i = 0; i < n; i++)
    {
        std::cin >> arrA[i];
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> arrB[i];
    }
    for (int i = 0; i < n; i++)
    {
        product = arrA[i] * arrB[i];
        scalarProduct += product;
    }
    std::cout << "Scalar product is: " << scalarProduct << std::endl;
}

// a0, a1, a2, a3, ..., an
// b0, b1, b2, b3, ..., bn
// a0*b0 + a1*b1 + a2*b2 + ... an*bn

int main() {
    int n;
    std::cin>> n;
    ScalarProduct(n);
}