#include "Button.h"

Button::Button(sf::RenderWindow& inWindow, std::string inText, sf::Vector2f pos)
{
	window = &inWindow;
	btnText = inText;
	btnPos = pos;

	Setup();
}

void Button::Setup()
{
	if (!font.loadFromFile("Assets/Fonts/arial.ttf")) {}
	text = new sf::Text();

	text->setFont(font);
	text->setString(btnText);
	text->setCharacterSize(32);
	text->setFillColor(sf::Color::White);

	sf::Vector2f origin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
	text->setOrigin(origin);

	back = new sf::RectangleShape();
	sf::Vector2f size(text->getLocalBounds().width + 20, text->getLocalBounds().height + 20);
	back->setSize(size);
	back->setFillColor(sf::Color::Black);
	back->setOutlineColor(sf::Color::White);

	back->setOrigin(origin);

	text->setPosition(btnPos);
	back->setPosition(sf::Vector2f(btnPos.x - 10, btnPos.y));
}

void Button::Draw()
{
	window->draw(*back);
	window->draw(*text);
}

bool Button::Contains(sf::Vector2f pos)
{
	return back->getGlobalBounds().contains(pos);
}

void Button::Hovered(bool isHovered)
{
	if (isHovered)
	{
		back->setOutlineThickness(2);
	}
	else
	{

		back->setOutlineThickness(0);
	}
}

void Button::Clicked(bool isClicked)
{
	if (isClicked)
	{
		back->setFillColor(sf::Color::White);
		text->setFillColor(sf::Color::Black);
	}
	else
	{
		back->setFillColor(sf::Color::Black);
		text->setFillColor(sf::Color::White);
	}
}

void Button::Fire()
{
	EventManager::QueueEvent(event);
}

void Button::setEvent(CustomEvent inEvent)
{
	event = inEvent;
}