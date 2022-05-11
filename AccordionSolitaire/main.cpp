#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include "Game.h"
#include "GameScene.h"
#include "InstructionsScene.h"
#include "GameUI.h"

void processKeyboard(sf::RenderWindow& window, Game& game, sf::Event event);

bool started = false;

static bool settled = false;

double deltaTime = 0.0;
double lastTime = 0.0;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Accordion Solitaire", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	Game game(window);

	GameScene* gameScene = new GameScene(window);
	GameUI* gameUI = new GameUI(window, *gameScene);
	InstructionsScene* instrScene = new InstructionsScene(window);

	sf::Clock clock;
	int gameOverCheckInterval = 0;

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

			processKeyboard(window, game, event);

			if (!game.IsGameOver())
			{
				//processMouse(window, game, event);
				gameScene->ProcessMouse(event);
			}
		}

		window.clear(sf::Color::Color(0, 120, 0));

		if (started)
		{
			gameUI->Draw();

			gameScene->Draw();

			if (gameOverCheckInterval >= 1000)
			{
				if (game.IsGameOver())
				{
					if (!settled)
					{
						game.SettleGame();
					}
					settled = true;
					game.DrawGameOverScreen(window);
				}
				else
				{
					std::cout << gameOverCheckInterval << std::endl;
					gameOverCheckInterval = 0;
				}
			}
			gameOverCheckInterval += deltaTime;
		}
		else
		{
			instrScene->Draw();
		}

		window.display();

		sf::Time currentTime = clock.getElapsedTime();
		deltaTime = currentTime.asMilliseconds() - lastTime;
		lastTime = currentTime.asMilliseconds();
	}

	return 0;
}

void processKeyboard(sf::RenderWindow& window, Game& game, sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		settled = false;
		game.Reset(window);
		started = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		started = true;
	}
}