#include <iostream>

const int mat_size = 3;

void sortMatColumn(int mat[][mat_size]){
    for (int i = 0; i < mat_size; i++)
    {
        for (int j = 0; j < mat_size - 1; j++)
        {
            if(mat[i][j] > mat[i][j+1]){
                int temp = mat[i][j+1];
                mat[i][j+1] = mat[i][j];
                mat[i][j] = temp;
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
                                    {1,2,3},
                                    {0,6,4}};
    sortMatColumn(mat1);
    printmat(mat1);    
    return 0;
}