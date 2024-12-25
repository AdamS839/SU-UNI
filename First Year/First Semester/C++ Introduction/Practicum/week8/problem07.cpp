#include <iostream>

const int mat_size = 3;

void sortMatColumn(int mat[][mat_size]){
    for (int i = 0; i < mat_size; i++){
        for (int j = 0; j < mat_size; j++){
            for (int k = 0; k < mat_size - i - 1; k++){
                if (mat[k][j] > mat[k + 1][j]) {
                    int temp = mat[k + 1][j];
                    mat[k + 1][j] = mat[k][j];
                    mat[k][j] = temp;
                }
            }
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
    int mat1[mat_size][mat_size] = {{3,2,1},
                                    {1,8,9},
                                    {0,6,4}};
    sortMatColumn(mat1);
    printmat(mat1);    
    return 0;
}