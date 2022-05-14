#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include "Game.h"
#include "GameScene.h"
#include "InstructionsScene.h"
#include "GameOverScene.h"
#include "GameUI.h"
#include "EventManager.h"
#include "Enums.h"

void processKeyboard(sf::RenderWindow& window, sf::Event event);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Accordion Solitaire", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	GameScene* gameScene = new GameScene(window);
	GameUI* gameUI = new GameUI(window, *gameScene);
	InstructionsScene* instrScene = new InstructionsScene(window);
	GameOverScene* gameOverScene = new GameOverScene(window);

	EventManager::init();

	Screen screen = Screen::Instructions;

	// run the program as long as the window stays open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// close the window when requested
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			processKeyboard(window, event);
			if (screen == Screen::Instructions)
			{
				instrScene->ProcessMouse(event);
			}
			if (screen == Screen::Play)
			{
				gameUI->ProcessKeyboard(event);
				gameScene->ProcessMouse(event);
			}
		}

		CustomEvent nextEvent = EventManager::DequeueEvent();
		if (nextEvent.screen == Screen::Global)
		{
			GlobalEvents event = static_cast<GlobalEvents>(nextEvent.event);
			switch (event)
			{
			case GlobalEvents::PlayGame:
				screen = Screen::Play;
				break;
			case GlobalEvents::GameOver:
				screen = Screen::GameOver;
				break;
			}
		}

		window.clear(sf::Color::Color(0, 120, 0));

		if (screen == Screen::Instructions)
		{
			instrScene->Update(nextEvent);
		}
		if (screen == Screen::Play)
		{
			gameUI->Update(nextEvent);
			gameScene->Update(nextEvent);
		}
		if (screen == Screen::GameOver)
		{
			gameUI->Draw();
			gameScene->Draw();
			gameOverScene->Update(nextEvent);
		}

		window.display();
	}

	return 0;
}

void processKeyboard(sf::RenderWindow& window, sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}
}