#include "InstructionsUI.h"

InstructionsUI::InstructionsUI(sf::RenderWindow& window) : UserInterface(window)
{
	Setup();
}

#pragma region UserInterfaceRequired
void InstructionsUI::Setup()
{
	if (!font.loadFromFile("Assets/Fonts/Accordion.otf")) {}

	sf::Vector2f center(window->getSize().x / 2, window->getSize().y / 2);

	text["title"] = new sf::Text();
	text["title"]->setFont(font);
	text["title"]->setCharacterSize(22);
	text["title"]->setFillColor(sf::Color::White);

	std::string textStr = "Accordion Solitaire!\n";
	textStr += "* Draw cards by clicking on the deck\n";
	textStr += "* Cards can be played on the last stack or the stack 3 away\n";
	textStr += "	if they match value or suit\n";
	textStr += "* Stacks can be combined similarly to cards\n";
	textStr += "* Special Rule! You can move a stack to the back of the Accordion\n";
	textStr += "	by placing it on the empty space at the end\n";
	textStr += "* Gain points by stacking cards and bringing them\n";
	textStr += "	to the front of the accordion, but lose points for\n";
	textStr += "	moving cards to the back or having more than one stack\n";
	textStr += "	in the end.\n* Have fun!";

	text["title"]->setString("Accordion Solitaire!");
	text["title"]->setPosition(sf::Vector2f(500, 50));

	buttons["menu"] = new Button(*window, "Main Menu", sf::Vector2f(center.x, center.y + 200));
	buttons["menu"]->setEvent(CustomEvent(Screen::Instructions, static_cast<int>(InstructionsEvents::ReturnToMenu)));

	ace_clubs->CreateSprite();
	ace_diamonds->CreateSprite();
	jack_spades->CreateSprite();
	five_hearts->CreateSprite();
}

void InstructionsUI::Draw()
{
	std::map<std::string, sf::Text*>::iterator txtItr;
	for (txtItr = text.begin(); txtItr != text.end(); ++txtItr)
	{
		window->draw(*txtItr->second);
	}

	std::map<std::string, Button*>::iterator btnItr;
	for (btnItr = buttons.begin(); btnItr != buttons.end(); ++btnItr)
	{
		btnItr->second->Draw();
	}

	sf::Shader card;
	if(!card.loadFromFile("card.vert", "bright.frag")) {}
	
	ace_clubs->DrawOnScreen(*window, sf::Vector2f(200, 200), card);
	ace_diamonds->DrawOnScreen(*window, sf::Vector2f(250, 200), card);

	ace_clubs->DrawOnScreen(*window, sf::Vector2f(200, 250), card);
	jack_spades->DrawOnScreen(*window, sf::Vector2f(250, 250), card);
	five_hearts->DrawOnScreen(*window, sf::Vector2f(300, 250), card);
	ace_diamonds->DrawOnScreen(*window, sf::Vector2f(350, 250), card);
}
#pragma endregion UserInterfaceRequired
