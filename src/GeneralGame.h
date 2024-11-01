// A Chao Thao
// Sprint 3
// 11/01/2024

#ifndef GENERALGAME_H
#define GENERALGAME_H

#include "SOSGameLogic.h"
// GeneralGame class is derived from the SOSGameLogic class
class GeneralGame : public SOSGameLogic
{
public:
    GeneralGame(int size) : SOSGameLogic(size) {}
    bool CheckForSOS(int row, int col, char move, vector<pair<int, int>>& sosCells) override;
};

#endif