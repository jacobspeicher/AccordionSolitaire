#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include "Game.h"
#include "GameScene.h"
#include "InstructionsScene.h"
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
				gameScene->ProcessMouse(event);
			}
		}

		CustomEvent nextEvent = EventManager::DequeueEvent();
		if (nextEvent.type == CustomEventTypes::ChangeScene)
		{
			MainMenuEvents event = static_cast<MainMenuEvents>(nextEvent.eventData);
			switch (event)
			{
			case MainMenuEvents::PlayGame:
				screen = Screen::Play;
			}
		}

		window.clear(sf::Color::Color(0, 120, 0));

		if (screen == Screen::Instructions)
		{
			instrScene->Draw();
		}
		if (screen == Screen::Play)
		{
			gameUI->Draw();
			gameScene->Draw();
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
	}
}