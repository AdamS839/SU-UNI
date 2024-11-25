#include <iostream>

const int mat_size = 3; 

void rotateMat(int mat[mat_size][mat_size]){
    for (int i = 0; i < mat_size; i++) {
		for (int j = 0; j < i; j++) {
			std::swap(mat[i][j], mat[j][i]);
		}
	}

    for (int i = 0; i < mat_size; i++){
        for (int j = 0; j < mat_size / 2; j++){
            std::swap(mat[i][j], mat[i][mat_size - j - 1]);
        }
    }
    
}

void printMat(int mat[][mat_size]) {
    for (int i = 0; i < mat_size; i++) {
        for (int j = 0; j < mat_size; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int mat[mat_size][mat_size] = {{1,2,3},
                                   {4,5,6},
                                   {7,8,9}};

    rotateMat(mat);
    printMat(mat);
    return 0;
}