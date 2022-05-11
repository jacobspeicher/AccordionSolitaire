#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Card.h"

class Instructions
{
public:
	// constructor
	Instructions();

	// set up the font
	void SetupFont();

	// set up the text
	void SetupText();

	// draw the instructions on the screen
	void DrawInstructions(sf::RenderWindow& window);

private:
	sf::Font font;
	sf::Text instructions;
	sf::Text start;
};

