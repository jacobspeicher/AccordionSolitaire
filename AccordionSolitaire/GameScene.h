#pragma once
#include "Scene.h"
#include "Game.h"

class GameScene : protected Scene
{
public:
	// constructor
	GameScene(sf::RenderWindow& window);

	// setup the game scene
	void Setup();

	// draw things on the screen
	void Draw();

	// process the mouse and perform appropriate actions
	void ProcessMouse(sf::Event event);

private:
	Game* game;

	// process the left mouse button
	void processLMBClicked(sf::Vector2f mousePos);

	// process the mouse movement
	void processMouseMoved(sf::Vector2f mousePos);
};

