#pragma once
#include <SFML/Graphics.hpp>
#include "CustomEvent.h"
#include "EventManager.h"
#include "Enums.h"
#include "Button.h"

class UserInterface
{
public:
	sf::Font font;
	std::map<std::string, sf::Text*> text;
	std::map<std::string, Button*> buttons;

	sf::RenderWindow* window;

	// constructor
	UserInterface(sf::RenderWindow& inWindow);

	virtual void Setup() = 0;
	virtual void Draw() = 0;
	virtual void ProcessMouse(sf::Event event) = 0;

private:
};

