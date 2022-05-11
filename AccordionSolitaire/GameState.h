#pragma once
#include <iostream>
#include "Stack.h"
#include "Card.h"

class GameState
{
public:
	// constructor
	GameState(
		int iScore,
		int iEmpty,
		int iStackedPoints,
		int iMoving,
		std::vector<std::vector<Card>> vStackCards,
		std::vector<Card> vDeckCards,
		Card cHand
	);

	// get whether the game is over or not
	bool getGameOver();

private:
	int score;
	int emptyEnabledStack;

	int stackedPoints;
	int movingPenalty;

	std::vector<std::vector<Card>> stackCards;

	std::vector<Card> deckCards;
	Card hand;

	bool gameOver;

	// check whether the game is over
	void checkGameOver();
};

