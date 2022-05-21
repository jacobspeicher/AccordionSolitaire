#include "UserInterface.h"

UserInterface::UserInterface(sf::RenderWindow& inWindow)
{
	window = &inWindow;
}

void UserInterface::ProcessMouse(sf::Event event)
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			processLMBHeld(mousePos);
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			processLMBClicked(mousePos);
		}
	}

	if (event.type == sf::Event::MouseMoved)
	{
		processMouseMoved(mousePos);
	}
}

void UserInterface::processLMBClicked(sf::Vector2f mousePos)
{
	std::map<std::string, Button*>::iterator btnItr;
	for (btnItr = buttons.begin(); btnItr != buttons.end(); ++btnItr)
	{
		if (btnItr->second->Contains(mousePos))
		{
			btnItr->second->Clicked(false);
			btnItr->second->Fire();
		}
	}
}

void UserInterface::processLMBHeld(sf::Vector2f mousePos)
{
	std::map<std::string, Button*>::iterator btnItr;
	for (btnItr = buttons.begin(); btnItr != buttons.end(); ++btnItr)
	{
		if (btnItr->second->Contains(mousePos))
		{
			btnItr->second->Clicked(true);
		}
		else
		{
			btnItr->second->Clicked(false);
		}
	}
}

void UserInterface::processMouseMoved(sf::Vector2f mousePos)
{
	std::map<std::string, Button*>::iterator btnItr;
	for (btnItr = buttons.begin(); btnItr != buttons.end(); ++btnItr)
	{
		if (btnItr->second->Contains(mousePos))
		{
			btnItr->second->Hovered(true);
		}
		else
		{
			btnItr->second->Clicked(false);
			btnItr->second->Hovered(false);
		}
	}
}