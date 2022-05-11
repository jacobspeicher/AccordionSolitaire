#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

// Suit
// Clubs	0
// Diamonds	1
// Hearts	2
// Spades	3

class Card
{
public:
	sf::Sprite sprite;

	int value;
	int suit;
	
	// performs look-up and assignment of suit/value to texture (sprite)
	Card();
	Card(int iValue, int iSuit);

	// set the texture path for the card
	void SetTexturePath();

	// create the sprite for the card
	void CreateSprite();

	// draws the card on the screen at the given position
	void DrawOnScreen(sf::RenderWindow& window, sf::Vector2f position, sf::Shader& shader);

	// getter and setter for texture path
	void setTexturePath(std::string sTexturePath);
	std::string getTexturePath();

private:
	char Suit[4] = { 'c', 'd', 'h', 's' };
	std::string texturePath;
	sf::Texture cardTexture;
};

