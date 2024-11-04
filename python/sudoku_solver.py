class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """

        def is_valid(board, row, col, num):
            # Check the row
            for j in range(9):
                if board[row][j] == num:
                    return False
            
            # Check the column
            for i in range(9):
                if board[i][col] == num:
                    return False
            
            # Check the 3x3 sub-box
            start_row, start_col = 3 * (row // 3), 3 * (col // 3)
            for i in range(start_row, start_row + 3):
                for j in range(start_col, start_col + 3):
                    if board[i][j] == num:
                        return False
            
            # If all checks pass, the number is valid
            return True
                
        def backtrack(board):
            for i in range(9):
                for j in range(9):
                    if board[i][j] == '.':  # Empty cell found
                        for num in '123456789':
                            if is_valid(board, i, j, num):
                                board[i][j] = num  # Place num in cell
                                if backtrack(board):  # Recursively try to solve the rest
                                    return True
                                board[i][j] = '.'  # Reset cell on failure
                        return False  # No valid placement found, backtrack
            return True  # Board solved

        backtrack(board)
