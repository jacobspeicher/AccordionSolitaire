#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(sf::RenderWindow& window) : Scene(window)
{
	Setup();
}

#pragma region SceneRequired
void MainMenuScene::Setup()
{
	mainMenuUI = new MainMenuUI(*window);
}

void MainMenuScene::Update(CustomEvent event)
{
	
}

void MainMenuScene::Draw()
{
	mainMenuUI->Draw();
}

void MainMenuScene::ProcessMouse(sf::Event event)
{
	mainMenuUI->ProcessMouse(event);
}
#pragma endregion SceneRequired