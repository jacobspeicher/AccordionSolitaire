#include "Game.h"

Game::Game(sf::RenderWindow& window)
{
	if (!cardShader.loadFromFile("card.vert", "dull.frag")) {}
	Setup(window);
}

void Game::Setup(sf::RenderWindow& window)
{
	locHand = sf::Vector2f(window.getSize().x / 2 + 90.0f, window.getSize().y - 126.0f);
	locDeck = sf::Vector2f(window.getSize().x / 2 - 90.0f, window.getSize().y - 126.0f);

	score = 0;
	deck = new Deck(false, locDeck);
	emptyEnabledStack = 0;

	hand.value = 0;
	hand.suit = 0;
	hand.CreateSprite();

	SetUpStacks();
	stacks[0].setEnabled(true);

	if (!font.loadFromFile("Assets/Fonts/Accordion.otf")) {}
}

void Game::Reset(sf::RenderWindow& window)
{
	finalScore = 0;
	penalty = 0;
	stackedPoints = 0;
	movingPenalty = 0;

	stacks.clear();
	stackPositions.clear();
	states.clear();
	Setup(window);
}

void Game::DrawCard()
{
	if(hand.value == 0 && deck->cards.size() > 0) 
	{
		Card drawnCard = deck->DrawCard();
		hand = drawnCard;
		hand.CreateSprite();

		for (int i = 0; i < emptyEnabledStack; ++i)
		{
			stacks[i].setEnabled(false);
		}

		determineValidCardPlacements();

		validCard = true;
	}
}

void Game::SetUpStacks()
{
	for (int i = 0; i < 27; ++i)
	{
		float xPos = 250.0f + (175.0f * (i % 9));
		float yPos = 150.0f + (275.0f * (i / 9));
		sf::Vector2f pos(xPos, yPos);
		stackPositions.push_back(pos);
		stacks.push_back(Stack({}, stackPositions.back(), i, "Assets/Fonts/Accordion.otf"));
	}

	for (int i = 0; i < 27; ++i)
	{
		stacks[i].CreateSprite();
	}
}

void Game::PlayCard(int stackIdx)
{
	stacks[stackIdx].AddCardToStack(hand);
	stacks[stackIdx].CreateSprite();

	hand.value = 0;
	hand.suit = 0;
	hand.CreateSprite();

	if (stackIdx == emptyEnabledStack)
	{
		++emptyEnabledStack;
		if (emptyEnabledStack < stacks.size())
		{
			stacks[emptyEnabledStack].setEnabled(true);
		}
	}

	//std::cout << "Played Card" << std::endl;
	//std::cout << "EmptyEnabledStack : " << emptyEnabledStack << std::endl;

	validCard = false;

	//std::cout << "Score : " << score << std::endl;
	saveGameState();
}

void Game::CombineStacks(int baseStackIdx, int piledStackIdx)
{
	std::vector<Card> baseStackCards = stacks[baseStackIdx].getCards();
	std::vector<Card> piledStackCards = stacks[piledStackIdx].getCards();
	baseStackCards.insert(baseStackCards.end(), piledStackCards.begin(), piledStackCards.end());
	Stack newStack(baseStackCards, stacks[baseStackIdx].getStackPosition(), baseStackIdx, "Assets/Fonts/Accordion.otf");

	stackedPoints += 10 * piledStackCards.size();
	score += 10 * piledStackCards.size();

	//printStacks();

	stacks[baseStackIdx] = newStack;
	stacks.erase(stacks.begin() + piledStackIdx);
	settleStacks(true);

	determineValidCardPlacements();

	//printStacks();

	//std::cout << "Score : " << score << std::endl;
	saveGameState();
}

void Game::MoveStackToEnd(int stackIdx)
{
	std::vector<Card> piledStackCards = stacks[stackIdx].getCards();
	Stack newStack(piledStackCards, stacks[emptyEnabledStack - 1].getStackPosition(), emptyEnabledStack - 1, "Assets/Fonts/Accordion.otf");

	movingPenalty += 7 * piledStackCards.size();
	score -= 7 * piledStackCards.size();

	stacks.erase(stacks.begin() + stackIdx);
	stacks[emptyEnabledStack - 1] = newStack;
	settleStacks(false);

	determineValidCardPlacements();
}

bool Game::IsGameOver()
{
	if (states.size() == 0)
	{
		return false;
	}
	return states.back().getGameOver();
}

std::map<std::string, int> Game::SettleGame()
{
	bonus = stacks[0].getSize() * 3;
	for (int i = 1; i < emptyEnabledStack; ++i)
	{
		penalty += stacks[i].getSize() * 5;
	}

	finalScore = score + bonus - penalty;
	std::map<std::string, int> scoreMap;
	scoreMap["finalScore"] = finalScore;
	scoreMap["stackedPoints"] = stackedPoints;
	scoreMap["bonus"] = bonus;
	scoreMap["movingPenalty"] = movingPenalty;
	scoreMap["penalty"] = penalty;

	return scoreMap;
}

// getters
bool Game::getHandPickedUp()
{
	return handPickedUp;
}

bool Game::getStackPickedUp()
{
	return stackPickedUp;
}

int Game::getPickedStackIndex()
{
	return pickedStackIdx;
}

int Game::getHoveredStackIndex()
{
	return hoveredStackIdx;
}

bool Game::getCardIsValid()
{
	return validCard;
}

bool Game::getStackIsValid(int idx)
{
	if (idx == -1)
	{
		return false;
	}

	if (pickedStackIdx - idx == 1 || pickedStackIdx - idx == 3)
	{
		if (stacks[idx].getTopCard().value == stacks[pickedStackIdx].getTopCard().value ||
			stacks[idx].getTopCard().suit == stacks[pickedStackIdx].getTopCard().suit)
		{
			return true;
		}
	}
	else if (idx == emptyEnabledStack)
	{
		return true;
	}

	return false;
}

bool Game::getStackCanBePickedUp(int idx)
{
	return idx < emptyEnabledStack;
}

int Game::getScore()
{
	return score;
}

int Game::getRightmostStack()
{
	return emptyEnabledStack == stacks.size() ? emptyEnabledStack - 1 : emptyEnabledStack;
}

// setters
void Game::setHandPickedUp(bool value)
{
	hand.ResetCenter();
	handPickedUp = value;
}

void Game::setStackPickedUp(bool value, int idx)
{
	stackPickedUp = value;

	if (!value)
	{
		stacks[pickedStackIdx].ResetStackOrigin();
		stacks[pickedStackIdx].ResetStackPosition();
		pickedStackIdx = -1;
	}
	else
	{
		pickedStackIdx = idx;
	}
}

void Game::setHoveredStackIndex(int idx)
{
	hoveredStackIdx = idx;
}

//private
void Game::determineValidCardPlacements()
{
	if (emptyEnabledStack > 0)
	{
		if (stacks[emptyEnabledStack - 1].getTopCard().value == hand.value ||
			stacks[emptyEnabledStack - 1].getTopCard().suit == hand.suit)
		{
			stacks[emptyEnabledStack - 1].setEnabled(true);
		}
	}
	if (emptyEnabledStack >= 3)
	{
		if (stacks[emptyEnabledStack - 3].getTopCard().value == hand.value ||
			stacks[emptyEnabledStack - 3].getTopCard().suit == hand.suit)
		{
			stacks[emptyEnabledStack - 3].setEnabled(true);
		}
	}
}

void Game::settleStacks(bool combined)
{
	for (int i = 0; i < stacks.size(); ++i)
	{
		stacks[i].setIndex(i);
		stacks[i].setStackPosition(stackPositions[i]);
		stacks[i].CreateSprite();
	}

	//std::cout << stacks.size() << std::endl;

	if (combined)
	{
		--emptyEnabledStack;
		//std::cout << emptyEnabledStack << std::endl;
		stacks.push_back(Stack({}, stackPositions.back(), stacks.size(), "Assets/Fonts/Accordion.otf"));
		stacks.back().CreateSprite();

		if (emptyEnabledStack == stacks.size() - 1)
		{
			stacks.back().setEnabled(true);
		}
	}
	else
	{
		stacks.push_back(Stack({}, stackPositions.back(), stacks.size(), "Assets/Fonts/Accordion.otf"));
		stacks.back().CreateSprite();

		if (emptyEnabledStack < stacks.size())
		{
			stacks[emptyEnabledStack].setEnabled(true);
		}
	}

	//std::cout << stacks.size() << std::endl;
}

void Game::saveGameState()
{
	std::vector<std::vector<Card>> stackCards;
	for (int i = 0; i < emptyEnabledStack; ++i)
	{
		stackCards.push_back(stacks[i].getCards());
	}

	GameState state(
		score,
		emptyEnabledStack,
		stackedPoints,
		movingPenalty,
		stackCards,
		deck->cards,
		hand
	);

	states.push_back(state);
}

void Game::printStacks()
{
	for (int i = 0; i < emptyEnabledStack; ++i)
	{
		std::cout << "Stack " << stacks[i].getIndex() << " : " << std::endl;
		std::cout << "    Size : " << stacks[i].getSize() << std::endl;
		std::cout << "    Cards : " << std::endl;

		std::vector<Card> cards = stacks[i].getCards();
		for (int j = 0; j < cards.size(); ++j)
		{
			std::cout << "        " << j << " : " << cards[j].value << ", " << cards[j].suit << std::endl;
		}
	}
	std::cout << std::endl;
}