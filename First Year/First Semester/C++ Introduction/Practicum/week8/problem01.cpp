#include <iostream>

const int size = 3;

void printMatrix(int matrix[size][size]){
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {

    int matrix[size][size] = {{1,2,3},
                              {4,5,6},
                              {7,8,9}};
    printMatrix(matrix);

    return 0;
}