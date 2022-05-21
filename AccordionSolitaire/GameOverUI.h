#pragma once
#include "UserInterface.h"
#include "CustomEvent.h"

class GameOverUI :
    public UserInterface
{
public:
    GameOverUI(sf::RenderWindow& window);

    // set up the game over UI
    void Setup();

    // draw the game over UI
    void Draw();
};

