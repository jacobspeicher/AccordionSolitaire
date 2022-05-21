#pragma once
#include "Scene.h"
#include "MainMenuUI.h"

class MainMenuScene :
    public Scene
{
public:
    MainMenuScene(sf::RenderWindow& window);

#pragma region SceneRequired
    void Setup();

    void Update(CustomEvent event);

    void Draw();

    void ProcessMouse(sf::Event event);
#pragma endregion SceneRequired
private:
    MainMenuUI* mainMenuUI;
};

