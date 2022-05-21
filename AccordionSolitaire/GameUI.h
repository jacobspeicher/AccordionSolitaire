#pragma once
#include "UserInterface.h"

class GameUI :
    public UserInterface
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
    //void ProcessMouse(sf::Event event);
#pragma endregion UserInterfaceRequired

    // set score
    void SetScore(int inScore);

    // set cards left
    void SetCardsLeft(int inCardsLeft);

private:
    int score;
    int cardsLeft;

    // process left mouse button click
    //void processLMBClicked(sf::Vector2f mousePos);

    // process left mouse button held
    //void processLMBHeld(sf::Vector2f mousePos);

    // process mouse movement
    //void processMouseMoved(sf::Vector2f mousePos);
};

