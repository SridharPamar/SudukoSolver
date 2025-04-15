#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 9;

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int row = 0; row < SIZE; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << "------+-------+------" << endl;
        }
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0 && col != 0) {
                cout << "| ";
            }
            if (grid[row][col] == 0) {
                cout << ". ";
            } else {
                cout << grid[row][col] << " ";
            }
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in the given position
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check row
    for (int x = 0; x < SIZE; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }
    
    // Check column
    for (int x = 0; x < SIZE; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }
    
    // Check 3x3 box
    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[boxStartRow + i][boxStartCol + j] == num) {
                return false;
            }
        }
    }
    
    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;
    bool isEmpty = false;
    
    // Find first empty cell
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }
    
    // If no empty cell, puzzle is solved
    if (!isEmpty) {
        return true;
    }
    
    // Try numbers 1-9
    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            
            if (solveSudoku(grid)) {
                return true;
            }
            
            // Backtrack
            grid[row][col] = 0;
        }
    }
    
    return false;
}

int main() {
    // Example Sudoku puzzle (0 represents empty cells)
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    cout << "Input Sudoku:" << endl;
    printGrid(grid);
    
    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku:" << endl;
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for the given Sudoku." << endl;
    }
    
    return 0;
}
