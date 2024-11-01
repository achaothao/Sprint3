// A Chao Thao
// Sprint 3
// 11/01/2024

#include "SOSGameLogic.h"

SOSGameLogic::SOSGameLogic(int size) : boardSize(size) {
    board = new char* [size];
    for (int i = 0; i < size; ++i)
        board[i] = new char[size];
    ClearBoard();
}

SOSGameLogic::~SOSGameLogic() {
    for (int i = 0; i < boardSize; ++i)
        delete[] board[i];
    delete[] board;
}

void SOSGameLogic::ResetBoard(int size) {
    for (int i = 0; i < boardSize; ++i)
        delete[] board[i];
    delete[] board;

    boardSize = size;
    board = new char* [size];
    for (int i = 0; i < size; ++i)
        board[i] = new char[size];
    ClearBoard();
}

// Check to see if each move in a specified cell is valid
bool SOSGameLogic::PlaceMove(int row, int col, char move) {
    if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != ' ')
        return false;

    board[row][col] = move;
    return true;
}

// Check to see if a cell is occupied
bool SOSGameLogic::IsCellOccupied(int row, int col) const {
    return board[row][col] != ' ';
}

// Check to see if the board is full
bool SOSGameLogic::IsBoardFull() const {
    for (int i = 0; i < boardSize; ++i)
        for (int j = 0; j < boardSize; ++j)
            if (board[i][j] == ' ')
                return false;
    return true;
}

// Clear the game board
void SOSGameLogic::ClearBoard() {
    for (int i = 0; i < boardSize; ++i)
        memset(board[i], ' ', boardSize);
}

int SOSGameLogic::GetBoardSize() const {
    return boardSize;
}