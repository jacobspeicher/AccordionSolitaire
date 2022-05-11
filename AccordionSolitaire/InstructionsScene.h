#pragma once
#include "Scene.h"
#include "Card.h"

class InstructionsScene :
    protected Scene
{
public:
    // constructor
    InstructionsScene(sf::RenderWindow& window);

    // setup the instructions screen
    void Setup();

    // draw the instructions screen
    void Draw();

    // process mouse events
    void ProcessMouse(sf::Event event);

private:
};

