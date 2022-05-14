#pragma once
#include "Scene.h"
#include "GameScene.h"

class GameUI :
    protected Scene
{
public:
    // constructor
    GameUI(sf::RenderWindow& window, GameScene& scene);

#pragma region SceneRequired
    // set up the game ui
    void Setup();

    // update the UI every frame
    void Update(CustomEvent event);

    // draw the game ui
    void Draw();

    // process mouse events
    void ProcessMouse(sf::Event event);
#pragma endregion SceneRequired

    // process keyboard events
    void ProcessKeyboard(sf::Event event);

private:
    GameScene* scene;
};

