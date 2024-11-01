// A Chao Thao
// Sprint 3
// 11/01/2024

#ifndef SOSGAME_H
#define SOSGAME_H

#include <wx/wx.h>
#include "SimpleGame.h"
#include "GeneralGame.h"

// All these functions are self explanatory
class SOSGame : public wxFrame
{
public:
    SOSGame(const wxString& sosgame);

    SOSGameLogic* GetGameLogic() const { return gameLogic; }


private:
    wxPanel* panel;
    wxRadioButton* simpleGameRadio;
    wxRadioButton* generalGameRadio;
    wxRadioButton* bluePlayerS;
    wxRadioButton* bluePlayerO;
    wxRadioButton* redPlayerS;
    wxRadioButton* redPlayerO;
    wxChoice* boardSizeChoice;
    wxStaticText* currentTurn;
    wxButton* newGameButton;

    // Display blue and red player score each time they make an SOS
    wxStaticText* bluePlayerPoints;
    wxStaticText* redPlayerPoints;

    vector<wxPanel*> cells;
    SOSGameLogic* gameLogic;  
    int currentPlayer;           
    int bluePlayerSOSCount;       
    int redPlayerSOSCount;      
    void CreateBoard(int size);                 
    void OnCellClicked(wxMouseEvent& event);    
    void OnNewGame();                           
    void UpdateCurrentTurn();                   
    void UpdatePointsDisplay();                 
    void ResetPlayerSelections();               
    bool SimpleGameMode() const;              
    bool GeneralGameMode() const;            

    wxDECLARE_EVENT_TABLE();
};

#endif