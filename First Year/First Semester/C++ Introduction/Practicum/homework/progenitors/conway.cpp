#include <iostream>
#include <cstdlib>   // For rand()
#include <ctime>     // For time()
#include <unistd.h>

const int grids = 20;

void printGrid(int grid[grids][grids]) {
    for (int i = 0; i < grids; i++) {
        for (int j = 0; j < grids; j++) {
            std::cout << (grid[i][j] ? '@' : '.') << " ";
        }
        std::cout << endl;
    }
}

int countNeighbors(int grid[grids][grids], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int ni = x + i, nj = y + j;
            if (ni >= 0 && ni < grids && nj >= 0 && nj < grids) {
                count += grid[ni][nj];
            }
        }
    }
    return count;
}

void nextGeneration(int grid[grids][grids]) {
    int newGrid[grids][grids] = {0};

    for (int i = 0; i < grids; i++) {
        for (int j = 0; j < grids; j++) {
            int neighbors = countNeighbors(grid, i, j);
            // rule of conway
            if (grid[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    newGrid[i][j] = 0;
                } else {
                    newGrid[i][j] = 1; 
                }
            } else {
                if (neighbors == 3) {
                    newGrid[i][j] = 1; 
                }
            }
            //
        }
    }

    for (int i = 0; i < grids; i++) {
        for (int j = 0; j < grids; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

void initializeGrid(int grid[grids][grids]) {
    srand(time(0)); 
    for (int i = 0; i < grids; i++) {
        for (int j = 0; j < grids; j++) {
            grid[i][j] = rand() % 2;
        }
    }
}

int main() {
    int finalGen = 100;
    int grid[grids][grids] = {0};
    initializeGrid(grid);
    
    for (int generation = 0; generation < finalGen; generation++) {
        std::cout << "Generation " << generation + 1 << ":\n";
        printGrid(grid); 
        nextGeneration(grid); 
    }

    return 0;
}
