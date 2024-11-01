// A Chao Thao
// Sprint 3
// 11/01/2024

#ifndef SOSGAMELOGIC_H
#define SOSGAMELOGIC_H

#include <vector>
using namespace std;

// These functions are self explainatory
class SOSGameLogic
{
public:
    SOSGameLogic(int size);
    virtual ~SOSGameLogic();
    virtual bool PlaceMove(int row, int col, char move);
    void ResetBoard(int size);
    int GetBoardSize() const;
    bool IsCellOccupied(int row, int col) const;
    virtual bool CheckForSOS(int row, int col, char move, vector<pair<int, int>>& sosCells) = 0;
    bool IsBoardFull() const;

protected:
    int boardSize;
    char** board;
    void ClearBoard();
};

#endif