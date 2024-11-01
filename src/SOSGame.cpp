// A Chao Thao
// Sprint 3
// 11/01/2024

#include "SOSGame.h"
#include <algorithm>
using namespace std;

wxBEGIN_EVENT_TABLE(SOSGame, wxFrame)
EVT_LEFT_DOWN(SOSGame::OnCellClicked)
wxEND_EVENT_TABLE()

SOSGame::SOSGame(const wxString& sosgame)
    : wxFrame(NULL, wxID_ANY, sosgame, wxDefaultPosition, wxSize(600, 400)), currentPlayer(0), bluePlayerSOSCount(0), redPlayerSOSCount(0)
{
    // Game pannel
    panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColour(255, 255, 255));

    // The rest are game components
    new wxStaticText(panel, wxID_ANY, "SOS", wxPoint(155, 5), wxDefaultSize, wxALIGN_LEFT);

    simpleGameRadio = new wxRadioButton(panel, wxID_ANY, "Simple Game", wxPoint(190, 5), wxDefaultSize, wxRB_GROUP);
    generalGameRadio = new wxRadioButton(panel, wxID_ANY, "General Game", wxPoint(330, 5));

    new wxStaticText(panel, wxID_ANY, "Board Size:", wxPoint(470, 5), wxDefaultSize, wxALIGN_LEFT);
    wxArrayString sizes;
    for (int i = 3; i <= 10; ++i)
        sizes.Add(wxString::Format("%d", i));

    boardSizeChoice = new wxChoice(panel, wxID_ANY, wxPoint(540, 5), wxDefaultSize, sizes);
    boardSizeChoice->SetSelection(0);

    new wxStaticText(panel, wxID_ANY, "Blue Player", wxPoint(10, 80), wxDefaultSize, wxALIGN_LEFT);
    bluePlayerS = new wxRadioButton(panel, wxID_ANY, "S", wxPoint(30, 120), wxDefaultSize, wxRB_GROUP);
    bluePlayerO = new wxRadioButton(panel, wxID_ANY, "O", wxPoint(30, 140));

    new wxStaticText(panel, wxID_ANY, "Red Player", wxPoint(470, 80), wxDefaultSize, wxALIGN_LEFT);
    redPlayerS = new wxRadioButton(panel, wxID_ANY, "S", wxPoint(490, 120), wxDefaultSize, wxRB_GROUP);
    redPlayerO = new wxRadioButton(panel, wxID_ANY, "O", wxPoint(490, 140));

    bluePlayerPoints = new wxStaticText(panel, wxID_ANY, "Blue Points: 0", wxPoint(10, 180), wxDefaultSize, wxALIGN_LEFT);
    redPlayerPoints = new wxStaticText(panel, wxID_ANY, "Red Points: 0", wxPoint(470, 180), wxDefaultSize, wxALIGN_LEFT);

    gameLogic = new SimpleGame(3);
    CreateBoard(3);

    currentTurn = new wxStaticText(panel, wxID_ANY, "Current Turn: Blue", wxPoint(250, 330), wxDefaultSize, wxALIGN_CENTER);

    newGameButton = new wxButton(panel, wxID_ANY, "New Game", wxPoint(500, 330));
    newGameButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { OnNewGame(); });

    boardSizeChoice->Bind(wxEVT_CHOICE, [this](wxCommandEvent&) { OnNewGame(); });
}

// Check to see if the player select simple game mode
bool SOSGame::SimpleGameMode() const
{
    return simpleGameRadio->GetValue();
}

// Check to see if the player select general game mode
bool SOSGame::GeneralGameMode() const
{
    return generalGameRadio->GetValue();
}

// Create game board dimension base on player choice
void SOSGame::CreateBoard(int size)
{
    for (auto& cell : cells)
        cell->Destroy();
    cells.clear();

    int xPosition = 160;
    int yPosition = 50;
    int boxWidth = 35;
    int boxHeight = 30;
    int gap = 34;

    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col)
        {
            wxPanel* cell = new wxPanel(panel, wxID_ANY, wxPoint(xPosition + (col * gap), yPosition + (row * boxHeight)),
                wxSize(boxWidth, boxHeight), wxSIMPLE_BORDER);
            cells.push_back(cell);
            cell->Bind(wxEVT_LEFT_DOWN, &SOSGame::OnCellClicked, this);
        }
    }
    gameLogic->ResetBoard(size);
    UpdateCurrentTurn();
}

// Handle click events for 'S' & 'O'
void SOSGame::OnCellClicked(wxMouseEvent& event)
{
    wxPanel* cell = dynamic_cast<wxPanel*>(event.GetEventObject());
    if (!cell) return;

    int index = find(cells.begin(), cells.end(), cell) - cells.begin();
    if (index < 0 || index >= cells.size()) return;

    int row = index / gameLogic->GetBoardSize();
    int col = index % gameLogic->GetBoardSize();

    // If player click on occupied cell
    if (gameLogic->IsCellOccupied(row, col))
    {
        wxMessageBox("This cell is already occupied! Please select a different cell.",
            "Invalid Move", wxOK | wxICON_ERROR);
        return;
    }

    char move = (currentPlayer == 0) ? (bluePlayerS->GetValue() ? 'S' : 'O') : (redPlayerS->GetValue() ? 'S' : 'O');

    if (gameLogic->PlaceMove(row, col, move))
    {
        wxStaticText* moveText = new wxStaticText(cell, wxID_ANY, wxString::Format("%c", move), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

        if (currentPlayer == 0) {
            moveText->SetForegroundColour(*wxBLUE);
        }
        else {
            moveText->SetForegroundColour(*wxRED);
        }

        vector<pair<int, int>> sosCells;
        if (gameLogic->CheckForSOS(row, col, move, sosCells))
        {
            if (currentPlayer == 0)
                ++bluePlayerSOSCount;
            else
                ++redPlayerSOSCount;

            UpdatePointsDisplay();

            // Draw a line through SOS that was made by the players
            // Blue line for blue player, red line for red player
            wxColour lineColor = (currentPlayer == 0) ? *wxBLUE : *wxRED;
            for (const auto& cellCoord : sosCells) {
                int cellIndex = cellCoord.first * gameLogic->GetBoardSize() + cellCoord.second;
                wxPanel* sosCell = cells[cellIndex];
                wxClientDC dc(sosCell);
                dc.SetPen(wxPen(lineColor, 2));

                if (sosCells[0].first == sosCells[2].first) {
                    dc.DrawLine(0, sosCell->GetSize().GetHeight() / 2, sosCell->GetSize().GetWidth(), sosCell->GetSize().GetHeight() / 2);
                }
                else if (sosCells[0].second == sosCells[2].second) {
                    dc.DrawLine(sosCell->GetSize().GetWidth() / 2, 0, sosCell->GetSize().GetWidth() / 2, sosCell->GetSize().GetHeight());
                }
                else if (sosCells[0].first < sosCells[2].first && sosCells[0].second < sosCells[2].second) {
                    dc.DrawLine(0, 0, sosCell->GetSize().GetWidth(), sosCell->GetSize().GetHeight());
                }
                else if (sosCells[0].first < sosCells[2].first && sosCells[0].second > sosCells[2].second) {
                    dc.DrawLine(sosCell->GetSize().GetWidth(), 0, 0, sosCell->GetSize().GetHeight());
                }
            }

            // Message display if a player win in a simple game
            if (SimpleGameMode())
            {
                wxString winner = (currentPlayer == 0) ? "Blue" : "Red";
                wxMessageBox(winner + " Wins!", "Congratulations!", wxOK | wxICON_INFORMATION);
                OnNewGame();
                return;
            }

            if (GeneralGameMode())
            {
                UpdateCurrentTurn();
                return;
            }
        }

        // Message display if its a draw in a simple game
        if (SimpleGameMode() && gameLogic->IsBoardFull())
        {
            wxMessageBox("It's a draw!", "Game Over!", wxOK | wxICON_INFORMATION);
            OnNewGame();
            return;
        }
        // Message display if a player win or draw in a general game
        else if (GeneralGameMode() && gameLogic->IsBoardFull())
        {
            if (bluePlayerSOSCount > redPlayerSOSCount)
                wxMessageBox("Blue Wins!", "Congratulations!", wxOK | wxICON_INFORMATION);
            else if (redPlayerSOSCount > bluePlayerSOSCount)
                wxMessageBox("Red Wins!", "Congratulations!", wxOK | wxICON_INFORMATION);
            else
                wxMessageBox("It's a draw!", "Game Over!", wxOK | wxICON_INFORMATION);

            OnNewGame();
            return;
        }

        currentPlayer = (currentPlayer + 1) % 2;
        UpdateCurrentTurn();
    }
}
// Game restart for new game
void SOSGame::OnNewGame()
{
    delete gameLogic;
    int boardSize = boardSizeChoice->GetSelection() + 3;
    gameLogic = SimpleGameMode() ? static_cast<SOSGameLogic*>(new SimpleGame(boardSize))
        : static_cast<SOSGameLogic*>(new GeneralGame(boardSize));

    CreateBoard(boardSize);
    ResetPlayerSelections();
    currentPlayer = 0;
    bluePlayerSOSCount = 0;
    redPlayerSOSCount = 0;
    UpdatePointsDisplay();
    UpdateCurrentTurn();
}

// Show players point
void SOSGame::UpdatePointsDisplay()
{
    bluePlayerPoints->SetLabel(wxString::Format("Blue Points: %d", bluePlayerSOSCount));
    redPlayerPoints->SetLabel(wxString::Format("Red Points: %d", redPlayerSOSCount));
}

void SOSGame::ResetPlayerSelections()
{
    bluePlayerS->SetValue(true);
    redPlayerS->SetValue(true);
}

// Show which player making the next move
void SOSGame::UpdateCurrentTurn()
{
    if (!currentTurn) {
        return;
    }
    wxString turn = (currentPlayer == 0) ? "Current Turn: Blue" : "Current Turn: Red";
    currentTurn->SetLabel(turn);
}


class SOSApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(SOSApp)

bool SOSApp::OnInit()
{
    SOSGame* game = new SOSGame("SOS Game");
    game->Show(true);
    return true;
}