#include <iostream>

const int mat_sizeR = 2;
const int mat_sizeC = 4;

void printMatWithMostUpper(char mat[mat_sizeR][mat_sizeC]){
    int maxcount = 0;
    int counter = 0;
    int defI= -1;
    int defJ = -1;
    for (int i = 0; i < mat_sizeR; i++)
    {
        for (int j = 0; j < mat_sizeC; j++)
        {
            if(mat[i][j] >= 'A' && mat[i][j] <= 'Z'){
                counter++;
            }
        }
    }
   
    
    
}

int main() {


    return 0;
}