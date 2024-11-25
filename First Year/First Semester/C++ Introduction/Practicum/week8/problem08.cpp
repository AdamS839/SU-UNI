#include <iostream>

const int mat_size = 2;

void printMat(int mat[][mat_size]){
    for (int i = 0; i < mat_size; i++)
    {
        for (int j = 0; j < mat_size; j++)
        {
            std::cout << mat[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    
}

int main() {
    int mat1[mat_size][mat_size] = {{2,8},
                                    {3,6}};
    int mat2[mat_size][mat_size] = {{1,3},
                                    {7,4}};
                                    
    int productmat[mat_size][mat_size];
    for (int i = 0; i < mat_size; i++){
        for (int j = 0; j < mat_size; j++){
            productmat[i][j] = 0;
            for (int k = 0; k < mat_size; k++){
                productmat[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    printMat(productmat);
    return 0;
}