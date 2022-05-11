#pragma once
#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Stack.h"
#include "GameState.h"

class Game
{
public:
	std::vector<Stack> stacks;
	std::vector<sf::Vector2f> stackPositions;

	Deck* deck;
	Card hand;

	// placement locations
	sf::Vector2f locHand;
	sf::Vector2f locDeck;

	// create the game controller
	Game(sf::RenderWindow& window);

	// set up the game
	void Setup(sf::RenderWindow& window);

	// reset the game
	void Reset(sf::RenderWindow& window);

	// create the stack lists
	void SetUpStacks();

	// draw a card into the players hand
	void DrawCard();

	// play a card on a stack
	void PlayCard(int stackIdx);

	// combine two stacks into one new stack
	// piledStack will control how many points the player gets for this action
	void CombineStacks(int baseStackIdx, int piledStackIdx);

	// move a stack to the end of the accordion
	// movedStack will control how many points the player loses for this action
	void MoveStackToEnd(int stackIdx);

	// check whether the game is over
	bool IsGameOver();

	// settle up the game, compute the final score, all that
	void SettleGame();

	// draw all the end-of-game metrics
	void DrawGameOverScreen(sf::RenderWindow& window);

	// getter and setter for picking up the card in hand
	void setHandPickedUp(bool value);
	bool getHandPickedUp();

	// getter for checking that the card in hand is valid
	bool getCardIsValid();

	// getter for checking that the stack is valid
	bool getStackIsValid(int idx);

	// getter for checking that the stack can be picked up
	bool getStackCanBePickedUp(int idx);

	// getter and setter for picking up a stack
	void setStackPickedUp(bool value, int idx);
	bool getStackPickedUp();
	int getPickedStackIndex();

	// getter and setter for what stack the user is currently hovering
	void setHoveredStackIndex(int idx);
	int getHoveredStackIndex();

	// getter for the score
	int getScore();

	// getter for the rightmost enabled stack
	int getRightmostStack();

private:
	bool handPickedUp = false;
	bool stackPickedUp = false;

	bool validCard = false;

	int score;
	int emptyEnabledStack = 0;
	int	pickedStackIdx = -1;
	int hoveredStackIdx = -1;

	int finalScore = 0;
	int stackedPoints = 0;
	int movingPenalty = 0;
	int bonus = 0;
	int penalty = 0;

	sf::Font font;

	std::vector<GameState> states;

	sf::Shader cardShader;

	// determine valid placements for the card in hand
	void determineValidCardPlacements();

	// settle up the stacks after combining or moving
	void settleStacks(bool combined);

	// save the game state and store it in the vector
	void saveGameState();

	// print all the stacks to the console
	void printStacks();
};

