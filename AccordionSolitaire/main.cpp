#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>

#include "Game.h"
#include "Instructions.h"

void processKeyboard(sf::RenderWindow& window, Game& game, sf::Event event);
void processMouse(sf::RenderWindow& window, Game& game, sf::Event event);

bool drawingCard = false;
bool started = false;

sf::Shader cardShader;
sf::Shader deckShader;
sf::Shader stackShader;

sf::Font font; 

sf::Text title;
sf::Text subtitle;
sf::Text score;
sf::Text cardsLeft;
sf::Text resetText;
sf::Text gameOver;
sf::Text version;

static bool settled = false;

double deltaTime = 0.0;
double lastTime = 0.0;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Accordion Solitaire", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	Game game(window);
	Instructions instructions;

	if (!cardShader.loadFromFile("card.vert", "dull.frag")) {}
	if (!deckShader.loadFromFile("card.vert", "dull.frag")) {}
	if (!stackShader.loadFromFile("card.vert", "bright.frag")) {}

	if (!font.loadFromFile("Accordion.otf")) {}

	title.setFont(font);
	subtitle.setFont(font);
	score.setFont(font);
	cardsLeft.setFont(font);
	resetText.setFont(font);
	gameOver.setFont(font);
	version.setFont(font);

	title.setString("Accordion Solitaire");
	subtitle.setString("by Jacob Speicher");
	resetText.setString("R to Reset");
	gameOver.setString("Game Over");
	version.setString("v1.3.1");

	title.setCharacterSize(22);
	subtitle.setCharacterSize(18);
	score.setCharacterSize(18);
	cardsLeft.setCharacterSize(18);
	resetText.setCharacterSize(18);
	gameOver.setCharacterSize(22);
	version.setCharacterSize(10);

	title.setPosition(sf::Vector2f(250, 900));
	subtitle.setPosition(sf::Vector2f(300, 950));
	score.setPosition(sf::Vector2f(1500, 900));
	cardsLeft.setPosition(sf::Vector2f(1500, 950));
	resetText.setPosition(sf::Vector2f(1500, 1000));
	gameOver.setPosition(sf::Vector2f(1200, 900));
	version.setPosition(sf::Vector2f(20, 1050));

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
				processMouse(window, game, event);
			}
		}

		window.clear(sf::Color::Color(0, 120, 0));

		window.draw(title);
		window.draw(subtitle);
		window.draw(version);

		if (started)
		{
			window.draw(resetText);

			score.setString("Score : " + std::to_string(game.getScore()));
			window.draw(score);

			cardsLeft.setString("Cards Left : " + std::to_string(game.deck->cards.size()));
			window.draw(cardsLeft);

			for (int i = 0; i < game.stacks.size(); ++i)
			{
				if (game.getStackPickedUp() && (i == game.getPickedStackIndex()))
				{
					continue;
				}

				if (i <= game.getRightmostStack())
				{
					game.stacks[i].DrawStack(window, stackShader);
				}
				//game.stacks[i].DrawStack(window, stackShader);
			}

			game.deck->DrawDeckPile(window, deckShader);

			if (game.getHandPickedUp())
			{
				game.hand.DrawOnScreen(
					window,
					static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)),
					cardShader
				);
			}
			else
			{
				game.hand.DrawOnScreen(window, game.locHand, cardShader);
			}

			if (game.getStackPickedUp())
			{
				game.stacks[game.getPickedStackIndex()].DrawStack(
					window,
					static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)),
					stackShader
				);
			}

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
					window.draw(gameOver);
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
			instructions.DrawInstructions(window);
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

void processMouse(sf::RenderWindow& window, Game& game, sf::Event event)
{
	sf::Vector2f position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (game.deck->deckPile.getGlobalBounds().contains(position))
			{
				static int cardsDrawn = 0;
				game.DrawCard();
				++cardsDrawn;
				//std::cout << cardsDrawn << " : " << game.hand.value << ", " << game.hand.suit << std::endl;
			}

			bool justDroppedStack = false;
			for (int i = 0; i < game.stacks.size(); ++i)
			{
				if (game.stacks[i].getBaseStackSprite().getGlobalBounds().contains(position))
				{
					if (game.getHandPickedUp() && game.stacks[i].getEnabled())
					{
						game.PlayCard(i);
					}
					else if(!game.getHandPickedUp())
					{
						if (game.getStackPickedUp() && game.getStackIsValid(game.getHoveredStackIndex()))
						{
							if (i == game.getPickedStackIndex())
							{
								game.setStackPickedUp(false, i);

								if (game.getHoveredStackIndex() > -1 && i != game.getHoveredStackIndex())
								{
									if (game.getHoveredStackIndex() == game.getRightmostStack())
									{
										game.MoveStackToEnd(i);
									}
									else
									{
										game.CombineStacks(game.getHoveredStackIndex(), i);
									}
								}
								//std::cout << "Combine Stack " << i << " with Stack " << game.getHoveredStackIndex() << std::endl;
							}
						}
						else if (game.getStackPickedUp() && !game.getStackIsValid(i))
						{
							game.setStackPickedUp(false, i);
							justDroppedStack = true;
						}
						else if (game.getStackCanBePickedUp(i) && !justDroppedStack)
						{
							float xPos = position.x - game.stacks[i].getBaseStackSprite().getGlobalBounds().left;
							float yPos = position.y - game.stacks[i].getBaseStackSprite().getGlobalBounds().top;
							game.stacks[i].setSpriteOrigin(sf::Vector2f(xPos, yPos));

							game.setStackPickedUp(true, i);
						}
					}
				}
			}

			if (game.hand.sprite.getGlobalBounds().contains(position) && !game.getHandPickedUp() && game.getCardIsValid())
			{
				game.setHandPickedUp(true);
				if (game.getHandPickedUp())
				{
					float xPos = position.x - game.hand.sprite.getGlobalBounds().left;
					float yPos = position.y - game.hand.sprite.getGlobalBounds().top;
					game.hand.sprite.setOrigin(sf::Vector2f(xPos, yPos));
				}
			}
			else if (game.getHandPickedUp())
			{
				game.setHandPickedUp(false);
			}
		}
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		if (game.deck->deckPile.getGlobalBounds().contains(position))
		{
			if (!deckShader.loadFromFile("card.vert", "bright.frag")) {}
		}
		else
		{
			if (!deckShader.loadFromFile("card.vert", "dull.frag")) {}
		}

		if (game.hand.sprite.getGlobalBounds().contains(position))
		{
			if (!cardShader.loadFromFile("card.vert", "bright.frag")) {}
		}
		else
		{
			if (!cardShader.loadFromFile("card.vert", "dull.frag")) {}
		}

		for (int i = 0; i < game.stacks.size(); ++i)
		{
			if (game.stacks[i].getBaseStackSprite().getGlobalBounds().contains(position))
			{
				if (i != game.getPickedStackIndex())
				{
					game.setHoveredStackIndex(i);
				}
			}
		}
		if (game.getHoveredStackIndex() > -1)
		{
			if (!game.stacks[game.getHoveredStackIndex()].getBaseStackSprite().getGlobalBounds().contains(position))
			{
				game.setHoveredStackIndex(-1);
			}
		}
	}
}