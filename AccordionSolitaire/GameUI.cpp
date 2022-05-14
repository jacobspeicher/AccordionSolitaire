#include "GameUI.h"

GameUI::GameUI(sf::RenderWindow& window, GameScene& inScene) : Scene(window)
{
	scene = &inScene;
	Setup();
}

#pragma region SceneRequired
void GameUI::Setup()
{
	if (!font.loadFromFile("Assets/Fonts/Accordion.otf")) {}

	text["title"] = new sf::Text();
	text["subtitle"] = new sf::Text();
	text["version"] = new sf::Text();

	text["score"] = new sf::Text();
	text["cardsLeft"] = new sf::Text();
	text["reset"] = new sf::Text();

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
	text["reset"]->setString("R to Reset");
	text["version"]->setString("v1.3.2");

	text["title"]->setPosition(sf::Vector2f(250, 900));
	text["subtitle"]->setPosition(sf::Vector2f(300, 950));
	text["score"]->setPosition(sf::Vector2f(1500, 900));
	text["cardsLeft"]->setPosition(sf::Vector2f(1500, 950));
	text["reset"]->setPosition(sf::Vector2f(1500, 1000));
	text["version"]->setPosition(sf::Vector2f(20, 1050));
}

void GameUI::Draw()
{
	text["score"]->setString("Score : " + std::to_string(scene->GetScore()));
	text["cardsLeft"]->setString("Cards Left : " + std::to_string(scene->GetCardsLeft()));

	std::map<std::string, sf::Text*>::iterator itr;
	for (itr = text.begin(); itr != text.end(); ++itr)
	{
		window->draw(*itr->second);
	}
}

void GameUI::ProcessMouse(sf::Event event)
{
}
#pragma endregion SceneRequired