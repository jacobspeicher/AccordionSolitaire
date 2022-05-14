#include "InstructionsScene.h"

InstructionsScene::InstructionsScene(sf::RenderWindow& window) : Scene(window)
{
	Setup();
}

void InstructionsScene::Setup()
{
	if (!font.loadFromFile("Assets/Fonts/Accordion.otf")) {}

	text["instr"] = new sf::Text();
	text["start"] = new sf::Text();

	text["instr"]->setFont(font);
	text["start"]->setFont(font);

	text["instr"]->setCharacterSize(18);
	text["start"]->setCharacterSize(22);

	text["instr"]->setFillColor(sf::Color::Black);

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

	text["instr"]->setString(textStr);
	text["instr"]->setPosition(sf::Vector2f(500, 300));

	text["start"]->setString("Press Enter to Start");
	sf::FloatRect startBounds = text["start"]->getLocalBounds();
	text["start"]->setOrigin(sf::Vector2f(startBounds.width / 2, startBounds.height / 2));
}

void InstructionsScene::Draw()
{
	sf::Vector2f center(window->getSize().x / 2, window->getSize().y / 2);
	Card instructionsCard;
	instructionsCard.sprite.setPosition(center);
	instructionsCard.sprite.setRotation(90);
	instructionsCard.sprite.setScale(sf::Vector2f(4, 4));

	text["start"]->setPosition(sf::Vector2f(center.x, center.y + 420));

	window->draw(instructionsCard.sprite);
	window->draw(*text["instr"]);
	window->draw(*text["start"]);
}

void InstructionsScene::ProcessMouse(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		CustomEvent event(CustomEventTypes::ChangeScene, static_cast<int>(MainMenuEvents::PlayGame));
		EventManager::QueueEvent(event);
	}
}