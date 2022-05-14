#pragma once
#include "Scene.h"
#include "Card.h"

class GameOverScene :
    public Scene
{
public:
    // constructor
    GameOverScene(sf::RenderWindow& window);

#pragma region SceneRequired
    // setup the game over screen
    void Setup();

    // update the game over scene with most recent event
    void Update(CustomEvent event);

    // draw the game over screen
    void Draw();

    // process mouse events on the game over screen
    void ProcessMouse(sf::Event event);
#pragma endregion SceneRequired

private:
    Card* backCard;
    
    int finalScore;
    int stackedPoints;
    int bonus;
    int movingPenalty;
    int penalty;
};

