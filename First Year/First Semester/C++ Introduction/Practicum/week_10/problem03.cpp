#include <iostream>

const int matsizeR = 4;
const int matsizeC = 5;

bool matpath(bool mat[matsizeR][matsizeC], int i, int j){
    if(mat[i][j] == 1) return false;
    if(i < 0 || i >= matsizeR) return false;
    if(j < 0 || j >= matsizeC) return false;
    if(i == matsizeR-1 && j == matsizeC-1) return true;
    mat[i][j] = true;
    bool path = matpath(mat,i-1, j) ||
                matpath(mat,i,j+1) || 
                matpath(mat,i+1,j) ||
                matpath(mat,i,j-1);
    mat[i][j] = false;
    return path;
}


int main() {

    bool mat[matsizeR][matsizeC] = {{0,0,0,0,0},
                                    {1,1,1,0,0},
                                    {1,1,1,1,0},
                                    {1,0,0,0,0}};

    std::cout << std::boolalpha << matpath(mat,0,0) << std::endl;
    return 0;
}