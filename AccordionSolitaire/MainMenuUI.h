#pragma once
#include "UserInterface.h"
class MainMenuUI :
    public UserInterface
{
public:
    MainMenuUI(sf::RenderWindow& window);

    // set up the game ui
    void Setup();

    // draw the game ui
    void Draw();

    // process mouse events
    void ProcessMouse(sf::Event event);
private:
    // process left mouse button click
    void processLMBClicked(sf::Vector2f mousePos);

    // process left mouse button held
    void processLMBHeld(sf::Vector2f mousePos);

    // process mouse movement
    void processMouseMoved(sf::Vector2f mousePos);
};