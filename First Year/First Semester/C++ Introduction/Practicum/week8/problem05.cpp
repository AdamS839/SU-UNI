#include <iostream>

const int mat_size = 3;

bool symetricMat(int mat[][mat_size]){
    for (int i = 0; i < mat_size; i++)
    {
        for (int j = 0; j < mat_size; j++)
        {
            if(mat[i][j] != mat[j][i]) return false;
        }
    }
    return true;
}

int main() {
    //sym
    int mat1[mat_size][mat_size] = {{1,1,-1},
                                    {1,2,0},
                                    {-1,0,5}};

    //antisym
    int mat2[mat_size][mat_size] = {{3,1,1},
                                    {3,4,0},
                                    {1,4,1}};

    std::cout << std::boolalpha << symetricMat(mat1) << std::endl;
    return 0;
}