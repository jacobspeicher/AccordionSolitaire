#include "Instructions.h"

Instructions::Instructions()
{
	SetupFont();
	SetupText();
}

void Instructions::SetupFont()
{
	if (!font.loadFromFile("Assets/Fonts/Accordion.otf")) {}
}

void Instructions::SetupText()
{
	instructions.setFont(font);
	instructions.setCharacterSize(18);
	instructions.setFillColor(sf::Color::Black);
	
	std::string text = "Accordion Solitaire!\n";
	text += "* Draw cards by clicking on the deck\n";
	text += "* Cards can be played on the last stack or the stack 3 away\n";
	text += "	if they match value or suit\n";
	text += "* Stacks can be combined similarly to cards\n";
	text += "* Special Rule! You can move a stack to the back of the Accordion\n";
	text += "	by placing it on the empty space at the end\n";
	text += "* Gain points by stacking cards and bringing them\n";
	text += "	to the front of the accordion, but lose points for\n";
	text += "	moving cards to the back or having more than one stack\n";
	text += "	in the end.\n* Have fun!";

	instructions.setString(text);
	instructions.setPosition(sf::Vector2f(500, 300));

	start.setFont(font);
	start.setCharacterSize(22);
	start.setString("Press Enter to Start");

	sf::FloatRect startBounds = start.getLocalBounds();
	start.setOrigin(sf::Vector2f(startBounds.width / 2, startBounds.height / 2));
}

void Instructions::DrawInstructions(sf::RenderWindow& window)
{
	sf::Vector2f center(window.getSize().x / 2, window.getSize().y / 2);
	Card instructionsCard;
	instructionsCard.sprite.setPosition(center);
	instructionsCard.sprite.setRotation(90);
	instructionsCard.sprite.setScale(sf::Vector2f(4, 4));

	start.setPosition(sf::Vector2f(center.x, center.y + 420));

	window.draw(instructionsCard.sprite);
	window.draw(instructions);
	window.draw(start);
}