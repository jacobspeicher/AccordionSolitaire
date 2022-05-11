#pragma once
#include <iostream>
#include "Card.h"

class Stack
{
public:
	// create a new stack of cards
	Stack(const std::vector<Card>& vCards, sf::Vector2f vStackPosition, int idx, std::string sFontName);

	// set up the stack texture
	void CreateSprite();

	// draw the stack (the top card of the stack)
	void DrawStack(sf::RenderWindow& window, sf::Shader& shader);
	void DrawStack(sf::RenderWindow& window, sf::Vector2f pos, sf::Shader& shader);

	// add cards to stack
	void AddCardToStack(Card card);

	// reset the stack position (if it's picked up and not dropped in a valid location)
	void ResetStackPosition();

	// getter and setter for stack position
	void setStackPosition(sf::Vector2f vStackPosition);
	sf::Vector2f getStackPosition();

	// getter and setter for enabled
	void setEnabled(bool bEnabled);
	bool getEnabled();

	// getter for the list of cards in the stack
	std::vector<Card> getCards();

	// getter for the sprite
	sf::Sprite getBaseStackSprite();

	// getter for the stacks index
	void setIndex(int idx);
	int getIndex();

	// setter for the stack sprite origin
	void setSpriteOrigin(sf::Vector2f pos);

	// getter for the size of the stack
	int getSize();

	// getter for the top card on the stack
	Card getTopCard();

private:
	std::vector<Card> cards;

	sf::Vector2f stackPosition;

	std::string texturePath;
	sf::Sprite baseStackSprite;
	sf::Texture baseStackTexture;

	sf::Font font;
	std::string fontName;
	sf::Text sizeText;

	bool enabled = false;

	int index;
	int size;

	// set up the stack texture path
	void SetTexturePath();

	// set the text for the stack size
	void SetSizeText();
};

