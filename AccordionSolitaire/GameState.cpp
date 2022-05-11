#include "GameState.h"

GameState::GameState(
	int iScore,
	int iEmpty,
	int iStackedPoints,
	int iMoving,
	std::vector<std::vector<Card>> vStackCards,
	std::vector<Card> vDeckCards,
	Card cHand
)
{
	score = iScore;
	emptyEnabledStack = iEmpty;
	stackedPoints = iStackedPoints;
	movingPenalty = iMoving;
	stackCards = vStackCards;
	deckCards = vDeckCards;
	hand = cHand;

	checkGameOver();
}

bool GameState::getGameOver()
{
	return gameOver;
}

// private
void GameState::checkGameOver()
{
	if (deckCards.size() == 0 && hand.value == 0)
	{
		for (int i = 1; i < emptyEnabledStack; ++i)
		{
			Card topCard = stackCards[i].back();
			Card previousCard = stackCards[i - 1].back();

			if (previousCard.value == topCard.value || previousCard.suit == topCard.suit)
			{
				gameOver = false;
				return;
			}

			if (i >= 3)
			{
				Card twoPreviousCard = stackCards[i - 3].back();
				if (twoPreviousCard.value == topCard.value || twoPreviousCard.suit == topCard.suit)
				{
					gameOver = false;
					return;
				}
			}
		}
		gameOver = true;
		return;
	}
	gameOver = false;
}