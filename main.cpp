#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Funktion, um das Sudoku von einer Datei einzulesen
vector<vector<int>> readSudoku(string filename) {
    vector<vector<int>> sudoku(9, vector<int>(9, 0));
    ifstream input(filename);
    if (input.is_open()) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                input >> sudoku[i][j];
            }
        }
    }
    input.close();
    return sudoku;
}

// Funktion, um das Sudoku auf der Konsole auszugeben
void printSudoku(vector<vector<int>> sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
}

// Funktion, um zu überprüfen, ob eine Zahl in einer bestimmten Zeile gültig ist
bool isValidInRow(vector<vector<int>> sudoku, int row, int num) {
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == num) {
            return false;
        }
    }
    return true;
}

// Funktion, um zu überprüfen, ob eine Zahl in einer bestimmten Spalte gültig ist
bool isValidInCol(vector<vector<int>> sudoku, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][col] == num) {
            return false;
        }
    }
    return true;
}

// Funktion, um zu überprüfen, ob eine Zahl in einem bestimmten 3x3-Block gültig ist
bool isValidInBlock(vector<vector<int>> sudoku, int row, int col, int num) {
    int rowStart = (row / 3) * 3;
    int colStart = (col / 3) * 3;
    for (int i = rowStart; i < rowStart + 3; i++) {
        for (int j = colStart; j < colStart + 3; j++) {
            if (sudoku[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}

// Funktion, um zu überprüfen, ob eine Zahl an einer bestimmten Position gültig ist
bool isValid(vector<vector<int>> sudoku, int row, int col, int num) {
    return isValidInRow(sudoku, row, num) && isValidInCol(sudoku, col, num) && isValidInBlock(sudoku, row, col, num);
}

// Funktion, um die erste leere Stelle im Sudoku zu finden
bool findEmpty(vector<vector<int>> sudoku, int &row, int &col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (sudoku[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Funktion, um das Sudoku zu lösen
bool solveSudoku(vector<vector<int>> &sudoku) {
    int row, col;
    if (!findEmpty(sudoku, row, col)) {
        return true;
    }
    for (int num = 1; num <= 9; num++) {
        if (isValid(sudoku, row, col, num)) {
            sudoku[row][col] = num;
            cout << "STEP zu Lösung:" << endl;
            printSudoku(sudoku);
            if (solveSudoku(sudoku)) {
                return true;
            }
            sudoku[row][col] = 0;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> sudoku = readSudoku("sudoku.txt");
    cout << "Original Sudoku:" << endl;
    printSudoku(sudoku);
    if (solveSudoku(sudoku)) {
        cout << "Solved Sudoku:" << endl;
        printSudoku(sudoku);
    }
    else {
        cout << "No solution found." << endl;
    }
    return 0;
}
