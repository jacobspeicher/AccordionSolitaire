#pragma once
#include "UserInterface.h"

class GameUI :
    protected UserInterface
{
public:
    // constructor
    GameUI(sf::RenderWindow& window);

#pragma region UserInterfaceRequired
    // set up the game ui
    void Setup();

    // draw the game ui
    void Draw();

    // process mouse events
    void ProcessMouse(sf::Event event);
#pragma endregion UserInterfaceRequired

    // set score
    void SetScore(int inScore);

    // set cards left
    void SetCardsLeft(int inCardsLeft);

private:
    int score;
    int cardsLeft;
};

