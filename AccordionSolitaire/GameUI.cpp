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
	//text["reset"] = new sf::Text();

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
	//text["reset"]->setString("R to Reset");
	text["version"]->setString("v1.3.2");

	text["title"]->setPosition(sf::Vector2f(250, 900));
	text["subtitle"]->setPosition(sf::Vector2f(300, 950));
	text["score"]->setPosition(sf::Vector2f(1500, 900));
	text["cardsLeft"]->setPosition(sf::Vector2f(1500, 950));
	//text["reset"]->setPosition(sf::Vector2f(1500, 1000));
	text["version"]->setPosition(sf::Vector2f(20, 1050));

	buttons["Reset"] = new Button(*window, "Reset", sf::Vector2f(1500, 1000));
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

void GameUI::ProcessMouse(sf::Event event)
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			processLMBHeld(mousePos);
		}
	}
	
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			processLMBClicked(mousePos);
		}
	}
	
	if (event.type == sf::Event::MouseMoved)
	{
		processMouseMoved(mousePos);
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

#pragma region private
void GameUI::processLMBClicked(sf::Vector2f mousePos)
{
	std::map<std::string, Button*>::iterator btnItr;
	for (btnItr = buttons.begin(); btnItr != buttons.end(); ++btnItr)
	{
		if (btnItr->second->Contains(mousePos))
		{
			btnItr->second->Clicked(false);
			if (btnItr->first == "Reset")
			{
				CustomEvent event(Screen::Play, static_cast<int>(PlayEvents::ResetGame));
				EventManager::QueueEvent(event);
			}
		}
	}
}

void GameUI::processLMBHeld(sf::Vector2f mousePos)
{
	std::map<std::string, Button*>::iterator btnItr;
	for (btnItr = buttons.begin(); btnItr != buttons.end(); ++btnItr)
	{
		if (btnItr->second->Contains(mousePos))
		{
			btnItr->second->Clicked(true);
		}
		else
		{
			btnItr->second->Clicked(false);
		}
	}
}

void GameUI::processMouseMoved(sf::Vector2f mousePos)
{
	std::map<std::string, Button*>::iterator btnItr;
	for (btnItr = buttons.begin(); btnItr != buttons.end(); ++btnItr)
	{
		if (btnItr->second->Contains(mousePos))
		{
			btnItr->second->Hovered(true);
		}
		else
		{
			btnItr->second->Clicked(false);
			btnItr->second->Hovered(false);
		}
	}
}
#pragma endregion private