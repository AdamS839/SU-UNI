#include <iostream>

void printDiag(int **mat, int n){
    for (int i = 0; i < n; i++)
    {
        std::cout << mat[i][n-i-1] << ' ';
    }
    std::cout << std::endl;
}

void printBelowDiag(int **mat, int n){
    for (int i = 1; i < n; i++)
    {
        int row = i;
        int col = n - 1;
        while (row < n && col >= 0)
        {
            std::cout << mat[row][col] << ' ';
            ++row;
            --col;
        }
        std::cout << std::endl;
    }
    
}

int main() {

    int n;
    std::cin >> n;
    int **mat = new int*[n];
    for (int i = 0; i < n; i++)
    {
        mat[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> mat[i][j];
        }
    }
    printDiag(mat, n);
    std::cout << std::endl;
    printBelowDiag(mat, n);

    for (int i = 0; i < n; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
    
    
    return 0;
}