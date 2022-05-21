#include "MainMenuUI.h"

MainMenuUI::MainMenuUI(sf::RenderWindow& window) : UserInterface(window)
{
	Setup();
}

#pragma region SceneRequired
void MainMenuUI::Setup()
{
	if (!font.loadFromFile("Assets/Fonts/Accordion.otf")) {}

	sf::Vector2f center(window->getSize().x / 2, window->getSize().y / 2);

	text["title"] = new sf::Text();
	text["title"]->setFont(font);
	text["title"]->setCharacterSize(32);
	text["title"]->setPosition(sf::Vector2f(center.x, center.y - 150));

	text["subtitle"] = new sf::Text();
	text["subtitle"]->setFont(font);
	text["subtitle"]->setCharacterSize(16);
	text["subtitle"]->setPosition(sf::Vector2f(center.x, center.y - 100));

	text["title"]->setString("Accordion Solitaire");
	text["subtitle"]->setString("by Jacob Speicher");

	sf::Vector2f titleCenter(text["title"]->getLocalBounds().width / 2, text["title"]->getLocalBounds().height / 2);
	text["title"]->setOrigin(titleCenter);

	buttons["play"] = new Button(*window, "Play", sf::Vector2f(center.x, center.y + 55));
	buttons["instr"] = new Button(*window, "Instructions", sf::Vector2f(center.x, center.y + 105));
	buttons["options"] = new Button(*window, "Options", sf::Vector2f(center.x, center.y + 155));
	buttons["quit"] = new Button(*window, "Quit", sf::Vector2f(center.x, center.y + 205));

	buttons["play"]->setEvent(CustomEvent(Screen::MainMenu, static_cast<int>(MainMenuEvents::PlayGame)));
	buttons["instr"]->setEvent(CustomEvent(Screen::MainMenu, static_cast<int>(MainMenuEvents::OpenInstructions)));
	buttons["options"]->setEvent(CustomEvent(Screen::MainMenu, static_cast<int>(MainMenuEvents::OpenOptions)));
	buttons["quit"]->setEvent(CustomEvent(Screen::MainMenu, static_cast<int>(MainMenuEvents::Quit)));
}

void MainMenuUI::Draw()
{
	std::map<std::string, sf::Text*>::iterator txtItr;
	for (txtItr = text.begin(); txtItr != text.end(); ++txtItr)
	{
		window->draw(*txtItr->second);
	}

	std::map<std::string, Button*>::iterator btnItr;
	for (btnItr = buttons.begin(); btnItr != buttons.end(); ++btnItr)
	{
		btnItr->second->Draw();
	}
}