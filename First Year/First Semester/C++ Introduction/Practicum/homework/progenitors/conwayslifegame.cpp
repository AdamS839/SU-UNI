#include <iostream>
#include <windows.h>

const int gridSize = 20;
const int cellMaxAge = 6;

//принтиране на полето - матрицата, като за живи клетки се използва '@', а за мъртви - '.'
void printGrid(bool grid[gridSize][gridSize]){
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            if(grid[i][j]) std::cout << '@' << ' ';
            else std::cout << '.' << ' ';
        }
        std::cout << std::endl;
    }
}

// Броят на съседните живи клетки
int countLiveNeighboringCells(bool grid[gridSize][gridSize], int x, int y){
    //{-1,-1} {-1,0} {-1,+1}
    //{0, -1} {0, 0} {0, +1}
    //{+1,-1} {+1,0} {+1,+1}
    int counter = 0; 
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if(i == 0 && j == 0) continue;
            int neighborRow = x + i;
            int neighborCol = y + j;
            //if inside grid
            if(neighborRow >= 0 && neighborRow < gridSize && 
               neighborCol >= 0 && neighborCol < gridSize){
                if(grid[neighborRow][neighborCol]) ++counter;
            }
        }
    }
    return counter;
}

// Устойчивостта на жива клетка в началото спрямо колко други живи клетки има в реда и колоната на клетка [i][j]
void calculateCellImmunityBasedOnAliveCellsInRowAndCol(bool grid[gridSize][gridSize], int resistanceGrid[gridSize][gridSize]){
    for (int i = 0; i < gridSize; i++){
        for (int j = 0; j < gridSize; j++){
            int rowLiveCells = 0;
            int colLiveCells = 0;
            for (int row = 0; row < gridSize; row++)
            {
                if(grid[row][j]) ++rowLiveCells;
            }
            for (int col = 0; col < gridSize; col++)
            {
                if(grid[i][col]) ++colLiveCells;
            }
            //самата клетка се премахва от броя
            if(grid[i][j]){
                --rowLiveCells;
                --colLiveCells;
            }
            resistanceGrid[i][j] = rowLiveCells + colLiveCells;
        }
    }
}

// Функция за следващото поколение клетки
void nextGeneration(bool grid[gridSize][gridSize], int ageGrid[gridSize][gridSize], int resistanceGrid[gridSize][gridSize]) {
    bool newGrid[gridSize][gridSize] = {false};
    int newAgeGrid[gridSize][gridSize] = {0};
    int newResistGrid[gridSize][gridSize] = {0};

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            int neighbors = countLiveNeighboringCells(grid, i, j);
            if(grid[i][j]){
                if((neighbors == 2 || neighbors == 3) && ageGrid[i][j] < cellMaxAge){
                    newGrid[i][j] = true;
                    newAgeGrid[i][j] = ageGrid[i][j] + 1;
                    newResistGrid[i][j] = resistanceGrid[i][j];
                }
                else if(resistanceGrid[i][j] > 0 && ageGrid[i][j] < cellMaxAge){
                    newGrid[i][j] = true;
                    newAgeGrid[i][j] = ageGrid[i][j] + 1;
                    newResistGrid[i][j] = resistanceGrid[i][j] - 1;
                }
                else {
                    newGrid[i][j] = false;
                    newAgeGrid[i][j] = 0;
                    newResistGrid[i][j] = 0;
                }
            }
            else {
                if(neighbors == 3){
                    newGrid[i][j] = true;
                    newAgeGrid[i][j] = 1;
                    newResistGrid[i][j] = 0;
                }
            }
        }
    }
    // новото поколение се прехвърля на старото
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = newGrid[i][j];
            ageGrid[i][j] = newAgeGrid[i][j];
            resistanceGrid[i][j] = newResistGrid[i][j];
        }
    }
}

// задаване на случайни клетки да са живи
void startupGrid(bool grid[gridSize][gridSize]) {
    srand(time(0));
    // int x,y;
    // char addAliveCell = 'n';
    // do
    // {
    //     std::cout << "Set a cell to be alive? (Y/n)\n";
    //     std::cin >> addAliveCell;
    //     std::cout << "Add X and Y coordinates (x y)\n";
    //     std::cin >> x >> y;
    //     grid[x][y] = true;
    // } while (addAliveCell != 'n' || addAliveCell != 'N');
    
    double probabilityToBeAlive = 0.1;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            //Клетка [i][j] ще е жива с шанс 1/10
            grid[i][j] = ((rand() % 100) < (probabilityToBeAlive * 100));
        }
    }
}

bool isGridEmpty(bool grid[gridSize][gridSize]) {
    bool empty = true;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j]) {
                empty = false;
            }
        }
    }
    if(empty) std::cout << "The next generation is empty" << std::endl;
    return empty;
}


int main() {
    int gridSizeInput;
    int finalGeneration;
    std::cin >> gridSizeInput;
    std::cin >> finalGeneration;
    bool grid[gridSize][gridSize] = {false};
    int agegrid[gridSize][gridSize] = {0};
    int resistgrid[gridSize][gridSize] = {0};

    // bool** grid = new bool*[gridSizeInput];
    // int** ageGrid = new int*[gridSizeInput];
    // int** resistGrid = new int*[gridSizeInput];

    startupGrid(grid);
    calculateCellImmunityBasedOnAliveCellsInRowAndCol(grid, resistgrid);

    int currentGen = 0;
    while (!isGridEmpty(grid) && currentGen < finalGeneration)
    {
        std::cout << "Generation " << currentGen << ":\n";
        printGrid(grid);
        nextGeneration(grid, agegrid, resistgrid); 
        ++currentGen;
        Sleep(500);
    }

    return 0;
}