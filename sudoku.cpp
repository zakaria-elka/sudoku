#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 9;
const int EMPTY = 0;

// Function to print the Sudoku grid with simple styling
void printGrid(const vector<vector<int>>& grid) {
    cout << "┌───────┬─────────┐" << endl;
    for (int i = 0; i < N; i++) {
        if (i > 0 && i % 3 == 0) {
            cout << "├────────┼───────┤" << endl;
        }
        for (int j = 0; j < N; j++) {
            if (j > 0 && j % 3 == 0) {
                cout << "│ ";
            }
            if (grid[i][j] == EMPTY) {
                cout << ". ";
            } else {
                cout << grid[i][j] << " ";
            }
        }
        cout << "│" << endl;
    }
    cout << "└───────┴─────────┘" << endl;
}

// Function to check if a number can be placed in a given cell
bool canPlace(vector<vector<int>>& grid, int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == EMPTY) {
                for (int num = 1; num <= N; num++) {
                    if (canPlace(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid)) {
                            return true;
                        }
                        grid[row][col] = EMPTY;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Function to generate a Sudoku puzzle by removing some numbers
void generateSudoku(vector<vector<int>>& grid, int numToKeep) {
    srand(time(0));
    while (numToKeep > 0) {
        int row = rand() % N;
        int col = rand() % N;
        if (grid[row][col] != EMPTY) {
            int temp = grid[row][col];
            grid[row][col] = EMPTY;
            numToKeep--;
        }
    }
}

int main() {
    vector<vector<int>> grid(N, vector<int>(N, EMPTY));

    solveSudoku(grid);

    generateSudoku(grid, 30); // Adjust the number of clues as needed

    cout << "Welcome to Sudoku!" << endl;
    printGrid(grid);
    cout << "Enjoy the game!" << endl;

    return 0;
}
