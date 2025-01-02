#include <iostream>
#include <windows.h>

const int cellMaxAge = 6;

//принтиране на полето - матрицата, като за живи клетки се използва '@', а за мъртви - '.'
void printGrid(bool** grid, int gridSizeInput){
    for (int i = 0; i < gridSizeInput; i++){
        for (int j = 0; j < gridSizeInput; j++){
            if(grid[i][j]) std::cout << '@' << ' ';
            else std::cout << '.' << ' ';
        }
        std::cout << std::endl;
    }
}

// Броят на съседните живи клетки
int countLiveNeighboringCells(bool** grid, int x, int y, int gridSizeInput){
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
            if(neighborRow >= 0 && neighborRow < gridSizeInput && 
               neighborCol >= 0 && neighborCol < gridSizeInput){
                if(grid[neighborRow][neighborCol]) ++counter;
            }
        }
    }
    return counter;
}

// Устойчивостта на жива клетка в началото спрямо колко други живи клетки има в реда и колоната на клетка [i][j]
void calculateCellImmunityBasedOnAliveCellsInRowAndCol(bool** grid, int** resistanceGrid, int gridSizeInput){
    for (int i = 0; i < gridSizeInput; i++){
        for (int j = 0; j < gridSizeInput; j++){
            int rowLiveCells = 0;
            int colLiveCells = 0;
            for (int row = 0; row < gridSizeInput; row++)
            {
                if(grid[row][j]) ++rowLiveCells;
            }
            for (int col = 0; col < gridSizeInput; col++)
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
void nextGeneration(bool** grid, int** ageGrid, int** resistanceGrid, int gridSizeInput) {
    bool** newGrid = new bool*[gridSizeInput];
    int** newAgeGrid = new int*[gridSizeInput];
    int** newResistGrid = new int*[gridSizeInput];
    for (int i = 0; i < gridSizeInput; i++)
    {
        newGrid[i] = new bool[gridSizeInput]();
        newAgeGrid[i] = new int[gridSizeInput]();
        newResistGrid[i] = new int[gridSizeInput]();
    }
    

    for (int i = 0; i < gridSizeInput; i++) {
        for (int j = 0; j < gridSizeInput; j++) {
            int neighbors = countLiveNeighboringCells(grid, i, j, gridSizeInput);
            if(grid[i][j]){
                //живеене
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
                //съживяване
                if(neighbors == 3){
                    newGrid[i][j] = true;
                    newAgeGrid[i][j] = 1;
                    newResistGrid[i][j] = 0;
                }
            }
        }
    }
    // новото поколение се прехвърля на старото
    for (int i = 0; i < gridSizeInput; i++) {
        for (int j = 0; j < gridSizeInput; j++) {
            grid[i][j] = newGrid[i][j];
            ageGrid[i][j] = newAgeGrid[i][j];
            resistanceGrid[i][j] = newResistGrid[i][j];
        }
    }

    for (int i = 0; i < gridSizeInput; i++) {
        delete[] newGrid[i];
        delete[] newAgeGrid[i];
        delete[] newResistGrid[i];
    }
    delete[] newGrid;
    delete[] newAgeGrid;
    delete[] newResistGrid;
}

// задаване на случайни клетки да са живи
void startupGrid(bool** grid, int gridSizeInput) {
    srand(time(0));

    double probabilityToBeAlive = 0.1;
    for (int i = 0; i < gridSizeInput; i++) {
        for (int j = 0; j < gridSizeInput; j++) {
            //Клетка [i][j] ще е жива с шанс 1/10
            grid[i][j] = ((rand() % 100) < (probabilityToBeAlive * 100));
        }
    }
}

bool isGridEmpty(bool** grid, int gridSizeInput) {
    bool empty = true;
    for (int i = 0; i < gridSizeInput; i++) {
        for (int j = 0; j < gridSizeInput; j++) {
            if (grid[i][j]) {
                empty = false;
            }
        }
    }
    if(empty) std::cout << "The next generation is empty" << std::endl;
    return empty;
}

void AddCellOfChoice(bool** grid, int gridSizeInput){
    int x, y;
    std::cout << "Input the coordinates of the cell you wish to be alive in order (X Y): ";
    std::cin >> x >> y;
    if(x >= 0 && x < gridSizeInput && y >= 0 && y < gridSizeInput){
        grid[x][y] = true;
        std::cout << "Cell [" << x << "][" << y << "] is alive" << std::endl; 
    }
    else{
        std::cout << "Wrong coordinates - numbers must be between 0 and "<< gridSizeInput - 1 << std::endl;
    }
}

int main() {
    int gridSizeInput;
    int finalGeneration;
    do
    {
        std::cout << "Input grid size number between 10 and 30" << std::endl;
        std::cin >> gridSizeInput;
    } while (gridSizeInput < 10 || gridSizeInput > 30);
    
    do
    {
        std::cout << "Input a final generation number to view" << std::endl;
        std::cin >> finalGeneration;
    } while (finalGeneration < 0);
    

    bool** grid = new bool*[gridSizeInput];
    int** ageGrid = new int*[gridSizeInput];
    int** resistGrid = new int*[gridSizeInput];

    for (int i = 0; i < gridSizeInput; i++)
    {
        grid[i] = new bool[gridSizeInput]();
        ageGrid[i] = new int[gridSizeInput]();
        resistGrid[i] = new int[gridSizeInput]();
    }
    startupGrid(grid, gridSizeInput);
    
    char wishToAddAgain = 'y';
    do
    {
        std::cout << "Do you wish to make a cell alive? (y/n): ";
        std::cin >> wishToAddAgain;
        if(wishToAddAgain == 'y') AddCellOfChoice(grid, gridSizeInput);
    } while (wishToAddAgain != 'n');
    

   
    calculateCellImmunityBasedOnAliveCellsInRowAndCol(grid, resistGrid, gridSizeInput);

    int currentGen = 0;
    while (!isGridEmpty(grid, gridSizeInput) && currentGen < finalGeneration)
    {
        std::cout << "Generation " << currentGen << ":\n";
        printGrid(grid, gridSizeInput);
        nextGeneration(grid, ageGrid, resistGrid, gridSizeInput); 
        ++currentGen;
        Sleep(500);
    }

    for (int i = 0; i < gridSizeInput; i++) {
        delete[] grid[i];
        delete[] ageGrid[i];
        delete[] resistGrid[i];
    }
    delete[] grid;
    delete[] ageGrid;
    delete[] resistGrid;

    return 0;
}