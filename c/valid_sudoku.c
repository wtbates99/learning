#include <stdbool.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    // Arrays to track seen numbers for rows, columns, and boxes
    bool rows[9][9] = {false};
    bool cols[9][9] = {false};
    bool boxes[9][9] = {false};

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.') {
                int num = board[i][j] - '1';  // Convert char '1'-'9' to index 0-8

                // Calculate the 3x3 sub-box index
                int boxIndex = (i / 3) * 3 + j / 3;

                // Check if the number has already been seen in the row, column, or box
                if (rows[i][num] || cols[j][num] || boxes[boxIndex][num]) {
                    return false;  // Invalid Sudoku
                }

                // Mark the number as seen in the row, column, and box
                rows[i][num] = true;
                cols[j][num] = true;
                boxes[boxIndex][num] = true;
            }
        }
    }
    return true;  // All checks passed
}

