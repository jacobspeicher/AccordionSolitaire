#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include "Game.h"
#include "GameScene.h"
#include "InstructionsScene.h"
#include "GameUI.h"

void processKeyboard(sf::RenderWindow& window, sf::Event event);

bool started = false;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Accordion Solitaire", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	GameScene* gameScene = new GameScene(window);
	GameUI* gameUI = new GameUI(window, *gameScene);
	InstructionsScene* instrScene = new InstructionsScene(window);

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
			gameScene->ProcessMouse(event);
		}

		window.clear(sf::Color::Color(0, 120, 0));

		if (started)
		{
			gameUI->Draw();

			gameScene->Draw();
		}
		else
		{
			instrScene->Draw();
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
		started = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		started = true;
	}
}