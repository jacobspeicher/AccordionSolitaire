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
	text["title"]->setCharacterSize(24);
	text["title"]->setFillColor(sf::Color::White);

	text["drawCards"] = new sf::Text();
	text["drawCards"]->setFont(font);
	text["drawCards"]->setCharacterSize(16);
	text["drawCards"]->setFillColor(sf::Color::White);

	text["playCards"] = new sf::Text();
	text["playCards"]->setFont(font);
	text["playCards"]->setCharacterSize(16);
	text["playCards"]->setFillColor(sf::Color::White);

	text["stacks"] = new sf::Text();
	text["stacks"]->setFont(font);
	text["stacks"]->setCharacterSize(16);
	text["stacks"]->setFillColor(sf::Color::White);

	text["special"] = new sf::Text();
	text["special"]->setFont(font);
	text["special"]->setCharacterSize(16);
	text["special"]->setFillColor(sf::Color::White);

	text["points"] = new sf::Text();
	text["points"]->setFont(font);
	text["points"]->setCharacterSize(16);
	text["points"]->setFillColor(sf::Color::White);

	std::string textStr = "Accordion Solitaire!\n";
	textStr += "* Stacks can be combined similarly to cards\n";
	textStr += "* Special Rule! You can move a stack to the back of the Accordion\n";
	textStr += "	by placing it on the empty space at the end\n";
	textStr += "* Gain points by stacking cards and bringing them\n";
	textStr += "	to the front of the accordion, but lose points for\n";
	textStr += "	moving cards to the back or having more than one stack\n";
	textStr += "	in the end.\n* Have fun!";

	text["title"]->setString("Accordion Solitaire!");
	int centerTitle = text["title"]->getLocalBounds().width / 2;
	text["title"]->setPosition(sf::Vector2f(center.x - centerTitle, 50));

	text["drawCards"]->setString("* Draw cards by clicking on the deck");
	text["drawCards"]->setPosition(sf::Vector2f(200, 200));

	text["playCards"]->setString("* Cards can be played at the end, the stack previous,\nor the stack 3 previous if they match value or suit");
	text["playCards"]->setPosition(sf::Vector2f(200, 400));

	text["stacks"]->setString("* Stacks can be combined with the same rules as playing cards");
	text["stacks"]->setPosition(sf::Vector2f(900, 200));

	text["special"]->setString("* Special Rule! You can move a stack to the back of the Accordion\nby placing it on the empty space at the end");
	text["special"]->setPosition(sf::Vector2f(900, 250));

	text["points"]->setString("* Gain points by stacking cards and bringing them to the front of the\nAccordion, but lose points for moving cards to the back or having\nmore than one stack by game over");
	text["points"]->setPosition(sf::Vector2f(900, 500));


	buttons["menu"] = new Button(*window, "Main Menu", sf::Vector2f(center.x, 800));
	buttons["menu"]->setEvent(CustomEvent(Screen::Instructions, static_cast<int>(InstructionsEvents::ReturnToMenu)));

	ace_clubs->CreateSprite();
	ace_diamonds->CreateSprite();
	jack_spades->CreateSprite();
	five_spades->CreateSprite();
	blank_card->CreateSprite();

	ace_clubs->sprite.setScale(0.5, 0.5);
	ace_diamonds->sprite.setScale(0.5, 0.5);
	jack_spades->sprite.setScale(0.5, 0.5);
	five_spades->sprite.setScale(0.5, 0.5);
	blank_card->sprite.setScale(0.5, 0.5);

	if (!deckTexture.loadFromFile("Assets/SaraCards/back.png")) {}
	deckPile.setTexture(deckTexture);
	deckPile.setOrigin(sf::Vector2f(deckPile.getLocalBounds().width / 2, deckPile.getLocalBounds().height / 2));
	deckPile.setScale(sf::Vector2f(0.5, 0.5));
	deckPile.setPosition(sf::Vector2f(300, 300));

	if (!arrowTexture.loadFromFile("Assets/arrow.png")) {}
	arrow.setTexture(arrowTexture);
	arrow.setOrigin(sf::Vector2f(arrow.getLocalBounds().width / 2, arrow.getLocalBounds().height / 2));
	arrow.setScale(sf::Vector2f(0.15, 0.15));
	arrow.setPosition(sf::Vector2f(1300, 400));
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

	window->draw(deckPile, &card);
	
	ace_clubs->DrawOnScreen(*window, sf::Vector2f(300, 550), card);
	blank_card->DrawOnScreen(*window, sf::Vector2f(400, 550), card);
	ace_diamonds->DrawOnScreen(*window, sf::Vector2f(500, 550), card);


	jack_spades->DrawOnScreen(*window, sf::Vector2f(300, 700), card);
	ace_clubs->DrawOnScreen(*window, sf::Vector2f(400, 700), card);
	ace_diamonds->DrawOnScreen(*window, sf::Vector2f(500, 700), card);
	blank_card->DrawOnScreen(*window, sf::Vector2f(600, 700), card);
	five_spades->DrawOnScreen(*window, sf::Vector2f(700, 700), card);

	ace_clubs->DrawOnScreen(*window, sf::Vector2f(1000, 400), card);
	jack_spades->DrawOnScreen(*window, sf::Vector2f(1100, 400), card);
	blank_card->DrawOnScreen(*window, sf::Vector2f(1200, 400), card);

	window->draw(arrow, &card);

	jack_spades->DrawOnScreen(*window, sf::Vector2f(1400, 400), card);
	ace_clubs->DrawOnScreen(*window, sf::Vector2f(1500, 400), card);
	blank_card->DrawOnScreen(*window, sf::Vector2f(1600, 400), card);
}
#pragma endregion UserInterfaceRequired
