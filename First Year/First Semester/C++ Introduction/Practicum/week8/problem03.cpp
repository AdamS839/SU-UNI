#include <iostream>

const int mat_size = 3;

void addMatrices(int mat1[mat_size][mat_size], int mat2[mat_size][mat_size]){
    for (int i = 0; i < mat_size; i++)
    {
        for (int j = 0; j < mat_size; j++)
        {
            mat1[i][j] += mat2[i][j];
        }
    }
}

int main() {
    int mat1[mat_size][mat_size] = {{1,2,3},
                                    {4,5,6},
                                    {7,8,9}};

    int mat2[mat_size][mat_size] = {{1,1,1},
                                    {2,2,2},
                                    {3,3,3}};

    addMatrices(mat1, mat2);

    for (int i = 0; i < mat_size; i++)
    {
        for (int j = 0; j < mat_size; j++)
        {
            std::cout << mat1[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    
    return 0;
}