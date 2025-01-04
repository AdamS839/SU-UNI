#include <iostream>
#include <cstdlib>   // For rand()
#include <ctime>     // For time()
#include <unistd.h>

using namespace std;

// Define the grid size
const int rows = 20;
const int cols = 20;

// Function to print the grid
void printGrid(int grid[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << (grid[i][j] ? '*' : '.') << " ";  // '*' for live cells, '.' for dead cells
        }
        cout << endl;
    }
}

// Function to count the number of live neighbors of a cell
int countNeighbors(int grid[rows][cols], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;  // Skip the cell itself
            int ni = x + i, nj = y + j;
            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                count += grid[ni][nj];  // Count live neighbors
            }
        }
    }
    return count;
}

// Function to compute the next generation
void nextGeneration(int grid[rows][cols]) {
    int newGrid[rows][cols] = {0};  // Create a new grid for the next generation

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = countNeighbors(grid, i, j);
            // Apply the rules of Conway's Game of Life
            if (grid[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    newGrid[i][j] = 0;  // The cell dies
                } else {
                    newGrid[i][j] = 1;  // The cell stays alive
                }
            } else {
                if (neighbors == 3) {
                    newGrid[i][j] = 1;  // The cell becomes alive
                }
            }
        }
    }

    // Copy the new grid back to the original grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

// Function to initialize the grid with random live cells
void initializeGrid(int grid[rows][cols]) {
    // Seed the random number generator
    srand(time(0));  // Use current time as the seed for randomness

    // Randomly populate the grid with live (1) or dead (0) cells
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = rand() % 2;  // Randomly set the cell to 0 or 1
        }
    }
}

int main() {
    // Initialize the grid with random live cells
    int grid[rows][cols] = {0};
    initializeGrid(grid);

    // Run the game for a certain number of generations
    for (int generation = 0; generation < 100; generation++) {
        cout << "Generation " << generation + 1 << ":\n";
        printGrid(grid);  // Print the current grid
        nextGeneration(grid);  // Calculate the next generation
        usleep(500000);  // Pause for half a second (for better visibility)
        //system("clear");  // Clear the console for the next generation
    }

    return 0;
}
