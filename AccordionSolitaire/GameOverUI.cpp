#include "GameOverUI.h"

GameOverUI::GameOverUI(sf::RenderWindow& window) : UserInterface(window)
{
	Setup();
}

void GameOverUI::Setup()
{
	sf::Vector2f center(window->getSize().x / 2, window->getSize().y / 2);

	buttons["mainmenu"] = new Button(*window, "Menu", sf::Vector2f(center.x - 110, center.y + 200));
	buttons["reset"] = new Button(*window, "Reset", sf::Vector2f(center.x, center.y + 200));
	buttons["quit"] = new Button(*window, "Quit", sf::Vector2f(center.x + 100, center.y + 200));

	buttons["mainmenu"]->setEvent(CustomEvent(Screen::GameOver, static_cast<int>(GameOverEvents::ReturnToMainMenu)));
	buttons["reset"]->setEvent(CustomEvent(Screen::GameOver, static_cast<int>(GameOverEvents::ResetGame)));
	buttons["quit"]->setEvent(CustomEvent(Screen::GameOver, static_cast<int>(GameOverEvents::Quit)));
}

void GameOverUI::Draw()
{
	std::map<std::string, Button*>::iterator btnItr;
	for (btnItr = buttons.begin(); btnItr != buttons.end(); ++btnItr)
	{
		btnItr->second->Draw();
	}
}
