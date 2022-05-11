#include "GameScene.h"

GameScene::GameScene(sf::RenderWindow& window) : Scene(window)
{
	Setup();
}

void GameScene::Setup()
{
	game = new Game(*window);

	shaders["Card"] = new sf::Shader();
	shaders["Deck"] = new sf::Shader();

	if (!shaders["Card"]->loadFromFile("card.vert", "dull.frag")) {}
	if (!shaders["Deck"]->loadFromFile("card.vert", "dull.frag")) {}

	shaders["Card"]->setUniform("alpha", 0.5f);
	shaders["Deck"]->setUniform("alpha", 0.5f);
}

void GameScene::Draw()
{
	for (int i = 0; i <= game->getRightmostStack(); ++i)
	{
		if (game->getStackPickedUp() && i == game->getPickedStackIndex())
		{
			continue;
		}
		game->stacks[i].DrawStack(*window, *shaders["Card"]);
	}

	game->deck->DrawDeckPile(*window, *shaders["Deck"]);

	if (game->getHandPickedUp())
	{
		game->hand.DrawOnScreen(
			*window,
			static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)),
			*shaders["Card"]
		);
	}
	else
	{
		game->hand.DrawOnScreen(*window, game->locHand, *shaders["Card"]);
	}

	if (game->getStackPickedUp())
	{
		game->stacks[game->getPickedStackIndex()].DrawStack(
			*window,
			static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)),
			*shaders["Deck"]
		);
	}
}

void GameScene::ProcessMouse(sf::Event event)
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));

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

#pragma region private
void GameScene::processLMBClicked(sf::Vector2f mousePos)
{
	if (game->deck->deckPile.getGlobalBounds().contains(mousePos))
	{
		game->DrawCard();
	}

	bool justDroppedStack = false;
	for (int i = 0; i <= game->getRightmostStack(); ++i)
	{
		if (game->stacks[i].getBaseStackSprite().getGlobalBounds().contains(mousePos))
		{
			if (game->getHandPickedUp() && game->stacks[i].getEnabled())
			{
				game->PlayCard(i);
			}
			else if (!game->getHandPickedUp())
			{
				if (game->getStackPickedUp() && game->getStackIsValid(game->getHoveredStackIndex()))
				{
					if (i == game->getPickedStackIndex())
					{
						game->setStackPickedUp(false, i);

						if (game->getHoveredStackIndex() > -1 && i != game->getHoveredStackIndex())
						{
							if (game->getHoveredStackIndex() == game->getRightmostStack())
							{
								game->MoveStackToEnd(i);
							}
							else
							{
								game->CombineStacks(game->getHoveredStackIndex(), i);
							}
						}
					}
				}
				else if (game->getStackPickedUp() && !game->getStackIsValid(i))
				{
					game->setStackPickedUp(false, i);
					justDroppedStack = true;
				}
				else if (game->getStackCanBePickedUp(i) && !justDroppedStack)
				{
					float xPos = mousePos.x - game->stacks[i].getBaseStackSprite().getGlobalBounds().left;
					float yPos = mousePos.y - game->stacks[i].getBaseStackSprite().getGlobalBounds().top;
					game->stacks[i].setSpriteOrigin(sf::Vector2f(xPos, yPos));

					game->setStackPickedUp(true, i);
				}
			}
		}
	}

	if (game->hand.sprite.getGlobalBounds().contains(mousePos) && !game->getHandPickedUp() && game->getCardIsValid())
	{
		game->setHandPickedUp(true);

		float xPos = mousePos.x - game->hand.sprite.getGlobalBounds().left;
		float yPos = mousePos.y - game->hand.sprite.getGlobalBounds().top;
		game->hand.sprite.setOrigin(sf::Vector2f(xPos, yPos));
	}
	else if (game->getHandPickedUp())
	{
		game->setHandPickedUp(false);
	}
}

void GameScene::processMouseMoved(sf::Vector2f mousePos)
{
	if (game->deck->deckPile.getGlobalBounds().contains(mousePos))
	{
		shaders["Deck"]->setUniform("alpha", 1.0f);
	}
	else
	{
		shaders["Deck"]->setUniform("alpha", 0.5f);
	}

	if (game->hand.sprite.getGlobalBounds().contains(mousePos))
	{
		shaders["Card"]->setUniform("alpha", 1.0f);
	}
	else
	{
		shaders["Card"]->setUniform("alpha", 0.5f);
	}

	for (int i = 0; i < game->getRightmostStack(); ++i)
	{
		if (game->stacks[i].getBaseStackSprite().getGlobalBounds().contains(mousePos))
		{
			if (i != game->getPickedStackIndex())
			{
				game->setHoveredStackIndex(i);
			}
		}
	}

	if (game->getHoveredStackIndex() > -1)
	{
		if (!game->stacks[game->getHoveredStackIndex()].getBaseStackSprite().getGlobalBounds().contains(mousePos))
		{
			game->setHoveredStackIndex(-1);
		}
	}
}
#pragma endregion