#include <iostream>

const int mat_sizeR = 4;
const int mat_sizeC = 20;

void mostUppercaseLetters(char mat[mat_sizeR][mat_sizeC]){
    int maxcount = 0;
    int defI= -1;

    for (int i = 0; i < mat_sizeR; i++)
    {
        int counter = 0;
        for (int j = 0; j < mat_sizeC; j++)
        {
            if(mat[i][j] >= 'A' && mat[i][j] <= 'Z'){
                counter++;
            }
        }
        if(counter > maxcount){
            maxcount = counter;
            defI = i;
        }

    }
    if (defI != -1)
    {
        std::cout << "Char with most uppercase letters is: "<< mat[defI] << std::endl;
    }
    else std::cout << "No char with uppercase letters found" << std::endl;
    
}

int main() {
    char matrix[mat_sizeR][mat_sizeC] = {"ASDASDaaa",
                                         "WHATTmfmf",
                                         "mamammaa",
                                         "amsmdamsdSS"
                                         };

    mostUppercaseLetters(matrix);
    return 0;
}