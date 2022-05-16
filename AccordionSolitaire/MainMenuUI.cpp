#include "MainMenuUI.h"

MainMenuUI::MainMenuUI(sf::RenderWindow& window) : UserInterface(window)
{
	Setup();
}

#pragma region SceneRequired
void MainMenuUI::Setup()
{

}

void MainMenuUI::Draw()
{

}

void MainMenuUI::ProcessMouse(sf::Event event)
{
	sf::Vector2f mousePos(static_cast<sf::Vector2f>(sf::Mouse::getPosition()));

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			processLMBClicked(mousePos);
		}
	}

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			processLMBHeld(mousePos);
		}
	}

	if (event.type == sf::Event::MouseMoved)
	{
		processMouseMoved(mousePos);
	}
}
#pragma endregion SceneRequired

#pragma region private
void MainMenuUI::processLMBClicked(sf::Vector2f mousePos)
{

}

void MainMenuUI::processLMBHeld(sf::Vector2f mousePos)
{

}

void MainMenuUI::processMouseMoved(sf::Vector2f mousePos)
{

}
#pragma endregion private