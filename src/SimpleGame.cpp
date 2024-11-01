// A Chao Thao
// Sprint 3
// 11/01/2024

#include "SimpleGame.h"

// Check for simple game mode rules
bool SimpleGame::CheckForSOS(int row, int col, char move, vector<pair<int, int>>& sosCells) {
    sosCells.clear();

    // Horizontal check: "S O S"
    if (col > 1 && board[row][col - 2] == 'S' && board[row][col - 1] == 'O' && board[row][col] == 'S') {
        sosCells = { {row, col - 2}, {row, col - 1}, {row, col} };
        return true;
    }
    if (col < boardSize - 2 && board[row][col] == 'S' && board[row][col + 1] == 'O' && board[row][col + 2] == 'S') {
        sosCells = { {row, col}, {row, col + 1}, {row, col + 2} };
        return true;
    }
    if (col > 0 && col < boardSize - 1 && board[row][col - 1] == 'S' && board[row][col] == 'O' && board[row][col + 1] == 'S') {
        sosCells = { {row, col - 1}, {row, col}, {row, col + 1} };
        return true;
    }

    // Vertical check: "S O S"
    if (row > 1 && board[row - 2][col] == 'S' && board[row - 1][col] == 'O' && board[row][col] == 'S') {
        sosCells = { {row - 2, col}, {row - 1, col}, {row, col} };
        return true;
    }
    if (row < boardSize - 2 && board[row][col] == 'S' && board[row + 1][col] == 'O' && board[row + 2][col] == 'S') {
        sosCells = { {row, col}, {row + 1, col}, {row + 2, col} };
        return true;
    }
    if (row > 0 && row < boardSize - 1 && board[row - 1][col] == 'S' && board[row][col] == 'O' && board[row + 1][col] == 'S') {
        sosCells = { {row - 1, col}, {row, col}, {row + 1, col} };
        return true;
    }

    // Diagonal check (top-left to bottom-right): "S O S"
    if (row > 1 && col > 1 && board[row - 2][col - 2] == 'S' && board[row - 1][col - 1] == 'O' && board[row][col] == 'S') {
        sosCells = { {row - 2, col - 2}, {row - 1, col - 1}, {row, col} };
        return true;
    }
    if (row < boardSize - 2 && col < boardSize - 2 && board[row][col] == 'S' && board[row + 1][col + 1] == 'O' && board[row + 2][col + 2] == 'S') {
        sosCells = { {row, col}, {row + 1, col + 1}, {row + 2, col + 2} };
        return true;
    }
    if (row > 0 && row < boardSize - 1 && col > 0 && col < boardSize - 1 && board[row - 1][col - 1] == 'S' && board[row][col] == 'O' && board[row + 1][col + 1] == 'S') {
        sosCells = { {row - 1, col - 1}, {row, col}, {row + 1, col + 1} };
        return true;
    }

    // Anti-diagonal check (top-right to bottom-left): "S O S"
    if (row > 1 && col < boardSize - 2 && board[row - 2][col + 2] == 'S' && board[row - 1][col + 1] == 'O' && board[row][col] == 'S') {
        sosCells = { {row - 2, col + 2}, {row - 1, col + 1}, {row, col} };
        return true;
    }
    if (row < boardSize - 2 && col > 1 && board[row][col] == 'S' && board[row + 1][col - 1] == 'O' && board[row + 2][col - 2] == 'S') {
        sosCells = { {row, col}, {row + 1, col - 1}, {row + 2, col - 2} };
        return true;
    }
    if (row > 0 && row < boardSize - 1 && col < boardSize - 1 && col > 0 && board[row - 1][col + 1] == 'S' && board[row][col] == 'O' && board[row + 1][col - 1] == 'S') {
        sosCells = { {row - 1, col + 1}, {row, col}, {row + 1, col - 1} };
        return true;
    }

    return false;
}