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
	Draw();

	if (event.screen == Screen::MainMenu)
	{
		CustomEvent* menuEvent = new CustomEvent();

		switch (static_cast<MainMenuEvents>(event.event))
		{
		case MainMenuEvents::PlayGame:
			menuEvent = new CustomEvent(Screen::Global, static_cast<int>(GlobalEvents::PlayGame));
			break;
		case MainMenuEvents::OpenInstructions:
			break;
		case MainMenuEvents::OpenOptions:
			break;
		case MainMenuEvents::Quit:
			window->close();
			break;
		}

		EventManager::QueueEvent(*menuEvent);
	}
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