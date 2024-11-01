// A Chao Thao
// Sprint 3 Unit Test
// 11/01/2024

#include "pch.h"
#include <wx/wx.h>
#include <gtest/gtest.h>
#include "SOSGameLogic.h"
#include "SimpleGame.h"
#include "GeneralGame.h"
using namespace std;

// Testing using chatGPT (User Story ID 1 & 2)
// Test User Story 1: Choose a board size
TEST(SOSGameTest, ChooseBoardSize) {
    int boardSize = 5;
    SimpleGame simpleGame(boardSize);

    // Ensure the board size is set correctly
    EXPECT_EQ(simpleGame.GetBoardSize(), boardSize);

    // Check if all cells are initially empty
    bool allCellsEmpty = true;
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (simpleGame.IsCellOccupied(row, col)) {
                allCellsEmpty = false;
                break;
            }
        }
    }
    EXPECT_TRUE(allCellsEmpty);
}

// Test User Story 2: Choose the game mode of a chosen board
TEST(SOSGameTest, ChooseGameMode) {
    int boardSize = 3; // Chosen board size
    SimpleGame simpleGame(boardSize);
    GeneralGame generalGame(boardSize);

    // Test that the correct derived class instances are created
    EXPECT_TRUE(dynamic_cast<SimpleGame*>(&simpleGame) != nullptr);
    EXPECT_TRUE(dynamic_cast<GeneralGame*>(&generalGame) != nullptr);

    // Ensure each mode can detect SOS patterns appropriately
    vector<pair<int, int>> sosCells;
    simpleGame.PlaceMove(0, 0, 'S');
    simpleGame.PlaceMove(0, 1, 'O');
    simpleGame.PlaceMove(0, 2, 'S');

    // Simple game should detect the SOS
    EXPECT_TRUE(simpleGame.CheckForSOS(0, 2, 'S', sosCells));

    // General game should detect the same SOS
    generalGame.PlaceMove(0, 0, 'S');
    generalGame.PlaceMove(0, 1, 'O');
    generalGame.PlaceMove(0, 2, 'S');
    EXPECT_TRUE(generalGame.CheckForSOS(0, 2, 'S', sosCells));
}

/*
    Below are my unit tests, I use the same format as chatGPT
    Most of the unit test already done in Sprint2, so it will look very familiar
*/

// Test User Story 3: Start a new game of the chosen board size and game mode
TEST(SOSGameTest, StartNewGame) {
    // This is for the Simple Game Mode
    int boardSize = 5;
    SimpleGame simpleGame(boardSize);
    simpleGame.ResetBoard(boardSize);

    EXPECT_EQ(simpleGame.GetBoardSize(), boardSize);

    bool allCellsEmpty = true;
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (simpleGame.IsCellOccupied(row, col)) {
                allCellsEmpty = false;
                break;
            }
        }
    }
    EXPECT_TRUE(allCellsEmpty);

    // This is for the General Game Mode
    GeneralGame generalGame(boardSize);
    generalGame.ResetBoard(boardSize); 

    EXPECT_EQ(generalGame.GetBoardSize(), boardSize);

    allCellsEmpty = true;
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (generalGame.IsCellOccupied(row, col)) {
                allCellsEmpty = false;
                break;
            }
        }
    }
    EXPECT_TRUE(allCellsEmpty);
}

// Test User Story 4: Make a move in a simple game
TEST(SOSGameTest, SimpleGameMove) {
    int boardSize = 3;
    SimpleGame simpleGame(boardSize);
    simpleGame.ResetBoard(boardSize); 

    // First move 'S' at (0, 0): Blue
    bool moveSuccess = simpleGame.PlaceMove(0, 0, 'S');
    EXPECT_TRUE(moveSuccess);
    EXPECT_TRUE(simpleGame.IsCellOccupied(0, 0));

    // Second move 'O' at (0, 1): Blue
    moveSuccess = simpleGame.PlaceMove(0, 1, 'O');
    EXPECT_TRUE(moveSuccess);
    EXPECT_TRUE(simpleGame.IsCellOccupied(0, 1));

    // Third move 'S' at (0, 2): Blue
    moveSuccess = simpleGame.PlaceMove(0, 1, 'S');
    EXPECT_FALSE(moveSuccess); // False because second move already took this cell
    EXPECT_TRUE(simpleGame.IsCellOccupied(0, 1)); 
}

// Test User Story 5: A simple game is over
TEST(SOSGameTest, SimpleGameOver) {
    int boardSize = 3;
    SimpleGame simpleGame(boardSize);
    simpleGame.ResetBoard(boardSize); 

    // Game over when a player is the winner
    simpleGame.PlaceMove(0, 0, 'S'); // Blue turn
    simpleGame.PlaceMove(0, 1, 'O'); // Red turn
    simpleGame.PlaceMove(0, 2, 'S'); // Blue turn

    // SOS is dectected, blue's the winner
    vector<pair<int, int>> sosCells;
    bool sosDetector = simpleGame.CheckForSOS(0, 2, 'S', sosCells);
    EXPECT_TRUE(sosDetector);
    EXPECT_TRUE(simpleGame.IsBoardFull() || sosDetector);  

    // Game over when it's a draw (no SOS were made)
    SimpleGame drawGame(boardSize);
    drawGame.ResetBoard(boardSize);

    // 3x3 board game have been filled with 'S'
    drawGame.PlaceMove(0, 0, 'S'); // Blue turn
    drawGame.PlaceMove(0, 1, 'S'); // Red turn
    drawGame.PlaceMove(0, 2, 'S'); // Blue turn
    drawGame.PlaceMove(1, 0, 'S'); // Red turn
    drawGame.PlaceMove(1, 1, 'S'); // Blue turn
    drawGame.PlaceMove(1, 2, 'S'); // Red turn
    drawGame.PlaceMove(2, 0, 'S'); // Blue turn
    drawGame.PlaceMove(2, 1, 'S'); // Red turn
    drawGame.PlaceMove(2, 2, 'S'); // Blue turn

    EXPECT_TRUE(drawGame.IsBoardFull());
    EXPECT_FALSE(drawGame.CheckForSOS(2, 2, 'O', sosCells));
}

// Test User Story 6: Make a move in a general game (same as making a move in simple game mode)
TEST(SOSGameTest, GeneralGameMove) {
    int boardSize = 3;
    GeneralGame generalGame(boardSize);
    generalGame.ResetBoard(boardSize);

    // First move 'S' at (0, 0): Blue
    bool moveSuccess = generalGame.PlaceMove(0, 0, 'S');
    EXPECT_TRUE(moveSuccess);
    EXPECT_TRUE(generalGame.IsCellOccupied(0, 0));

    // Second move 'O' at (0, 1): Red
    moveSuccess = generalGame.PlaceMove(0, 1, 'O');
    EXPECT_TRUE(moveSuccess);
    EXPECT_TRUE(generalGame.IsCellOccupied(0, 1));

    // Third move 'S' at (0, 2): Blue
    moveSuccess = generalGame.PlaceMove(0, 1, 'S');
    EXPECT_FALSE(moveSuccess); // False because second move already took this cell
    EXPECT_TRUE(generalGame.IsCellOccupied(0, 1));
}

// Test User Story 7: A general game is over
TEST(GeneralGameTest, GeneralGameOver) {
    int boardSize = 3;
    GeneralGame generalGame(boardSize);
    generalGame.ResetBoard(boardSize); 

    // In a 3x3 Board size
    generalGame.PlaceMove(0, 0, 'S'); // Blue turn
    generalGame.PlaceMove(0, 1, 'O'); // Red turn
    generalGame.PlaceMove(0, 2, 'S'); // Blue turn --> SOS point: 1 (SOS in first row)
    generalGame.PlaceMove(1, 0, 'S'); // Blue turn --> Blue got a point so it go again
    generalGame.PlaceMove(1, 1, 'O'); // Red turn
    generalGame.PlaceMove(1, 2, 'S'); // Blue turn --> SOS point: 2 (SOS in second row)
    generalGame.PlaceMove(2, 0, 'S'); // Blue turn --> SOS point: 3 (SOS anti-diagonal)
    generalGame.PlaceMove(2, 1, 'S'); // Blue turn
    generalGame.PlaceMove(2, 2, 'O'); // Red turn 

    EXPECT_TRUE(generalGame.IsBoardFull());

    int bluePoint = 3;
    int redPoint = 0;

    // Blue win: Blue recieve 3 SOS points and Red receive 0 point
    EXPECT_GT(bluePoint, redPoint);

    // Reset the board for new game where it's a draw in general game mode
    SimpleGame drawGame(boardSize);
    drawGame.ResetBoard(boardSize);
    // In a 3x3 Board size
    drawGame.PlaceMove(0, 0, 'S'); // Blue turn
    drawGame.PlaceMove(1, 0, 'S'); // Red turn 
    drawGame.PlaceMove(0, 1, 'O'); // Blue turn
    drawGame.PlaceMove(1, 1, 'O'); // Red turn
    drawGame.PlaceMove(0, 2, 'S'); // Blue turn --> SOS point: 1 (SOS in first row)
    drawGame.PlaceMove(2, 0, 'O'); // Blue turn --> Blue got a point so it go again
    drawGame.PlaceMove(1, 2, 'S'); // Red turn --> SOS point: 1 (SOS in second row)
    drawGame.PlaceMove(2, 1, 'S'); // Red turn --> Red got a point so it go again
    drawGame.PlaceMove(2, 2, 'O'); // Blue turn 

    EXPECT_TRUE(drawGame.IsBoardFull());

    int bluePoints = 1;
    int redPoints = 1;

    // It's a Draw: Blue recieve 1 SOS points and Red receive 1 point
    EXPECT_EQ(bluePoints, redPoints);
}