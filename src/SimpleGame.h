// A Chao Thao
// Sprint 3
// 11/01/2024

#ifndef SIMPLEGAME_H
#define SIMPLEGAME_H

#include "SOSGameLogic.h"

// The SimpleGame class is derived from the SOSGameLogic class
class SimpleGame : public SOSGameLogic
{
public:
    SimpleGame(int size) : SOSGameLogic(size) {}
    bool CheckForSOS(int row, int col, char move, vector<pair<int, int>>& sosCells) override;
};

#endif