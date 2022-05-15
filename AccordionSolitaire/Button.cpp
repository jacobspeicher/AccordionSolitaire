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
	if (!font.loadFromFile("Assets/Fonts/Accordion.otf")) {}
	text = new sf::Text();

	text->setFont(font);
	text->setString(btnText);
	text->setCharacterSize(18);
	text->setFillColor(sf::Color::Black);

	back = new sf::RectangleShape();
	sf::Vector2f size(text->getLocalBounds().width + 20, text->getLocalBounds().height + 20);
	back->setSize(size);
	back->setFillColor(sf::Color::White);

	text->setPosition(btnPos);
	back->setPosition(sf::Vector2f(btnPos.x - 10, btnPos.y - 10));
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