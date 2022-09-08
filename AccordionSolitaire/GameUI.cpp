#include "GameUI.h"

GameUI::GameUI(sf::RenderWindow& window) : UserInterface(window)
{
	Setup();
}

#pragma region UserInterfaceRequired
void GameUI::Setup()
{
	if (!font.loadFromFile("Assets/Fonts/Accordion.otf")) {}

	text["title"] = new sf::Text();
	text["subtitle"] = new sf::Text();
	text["version"] = new sf::Text();

	text["score"] = new sf::Text();
	text["cardsLeft"] = new sf::Text();

	std::map<std::string, sf::Text*>::iterator itr;
	for (itr = text.begin(); itr != text.end(); ++itr)
	{
		itr->second->setFont(font);
		itr->second->setCharacterSize(18);
	}

	text["title"]->setCharacterSize(22);
	text["version"]->setCharacterSize(10);

	text["title"]->setString("Accordion Solitaire");
	text["subtitle"]->setString("by Jacob Speicher");
	text["version"]->setString("v1.3.2");

	text["title"]->setPosition(sf::Vector2f(250, 900));
	text["subtitle"]->setPosition(sf::Vector2f(300, 950));
	text["score"]->setPosition(sf::Vector2f(1500, 900));
	text["cardsLeft"]->setPosition(sf::Vector2f(1500, 950));
	text["version"]->setPosition(sf::Vector2f(20, 1050));

	buttons["Reset"] = new Button(*window, "Reset", sf::Vector2f(1550, 1000));
	buttons["Reset"]->setEvent(CustomEvent(Screen::Play, static_cast<int>(PlayEvents::ResetGame)));
}

void GameUI::Draw()
{
	text["score"]->setString("Score : " + std::to_string(score));
	text["cardsLeft"]->setString("Cards Left : " + std::to_string(cardsLeft));

	std::map<std::string, sf::Text*>::iterator textItr;
	for (textItr = text.begin(); textItr != text.end(); ++textItr)
	{
		window->draw(*textItr->second);
	}

	std::map<std::string, Button*>::iterator btnItr;
	for (btnItr = buttons.begin(); btnItr != buttons.end(); ++btnItr)
	{
		btnItr->second->Draw();
	}
}
#pragma endregion UserInterfaceRequired

void GameUI::SetScore(int inScore)
{
	score = inScore;
}

void GameUI::SetCardsLeft(int inCardsLeft)
{
	cardsLeft = inCardsLeft;
}