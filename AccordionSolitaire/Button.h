#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	// constructor
	Button(sf::RenderWindow& window, std::string inText, sf::Vector2f pos);

	// set up the button
	void Setup();

	// draw the button on the screen
	void Draw();

	// check if the button contains a certain point
	bool Contains(sf::Vector2f pos);

	// change the button back when hovered
	void Hovered(bool isHovered);

	// change the button back when clicked
	void Clicked(bool isClicked);

private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text* text;
	sf::RectangleShape* back;

	std::string btnText;
	sf::Vector2f btnPos;
};

