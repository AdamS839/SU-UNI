#include <iostream>
const int mat_size = 3;

void transposeMat(int mat[][mat_size]){
    for (int i = 0; i < mat_size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }
}

void printmat(int mat[][mat_size]){
    for (int i = 0; i < mat_size; i++)
    {
        for (int j = 0; j < mat_size; j++)
        {
            std::cout << mat[i][j]<< ' ';
        }
        std::cout << std::endl;
    }
}

int main() {

    int mat1[mat_size][mat_size] = {{1,2,3},
                                    {4,5,6},
                                    {7,8,9}};

    transposeMat(mat1);
    printmat(mat1);
    return 0;
}