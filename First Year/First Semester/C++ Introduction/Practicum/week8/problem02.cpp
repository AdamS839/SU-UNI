#include <iostream>

const int mat_size = 5;

void findCoordinate(int mat[mat_size][mat_size], int n){
    int findI = -1;
    int findJ = -1;
    for (int i = 0; i < mat_size; i++)
    {
        for (int j = 0; j < mat_size; j++)
        {
            if(mat[i][j] == n){
                findI = i;
                findJ = j;
            }
        }
    }
    std::cout << findI << ' ' << findJ << std::endl; 
}

int main() {

    int mat[mat_size][mat_size] = {{1,2,3,4,5},
                                   {-1,-2,-3,-4,-5},
                                   {0,9,8,7,6},
                                   {13,12,11,15,16},
                                   {-6,-2,-7,-9,-20}};

    int n;
    std::cin >> n;

    int findI = -1;
    int findJ = -1;
    bool found = false;
    for (int i = 0; i < mat_size; i++)
    {
        for (int j = 0; j < mat_size; j++)
        {
            if(mat[i][j] == n){
                findI = i;
                findJ = j;
                found = true;
                break;
            }
        }
        if(found) break;
    }
    std::cout << findI << ' ' << findJ << std::endl;

    //findCoordinate(mat, n);
    return 0;
}