#pragma once
#include "Scene.h"
#include "Game.h"

class GameScene : protected Scene
{
public:
	// constructor
	GameScene(sf::RenderWindow& window);

#pragma region SceneRequired
	// setup the game scene
	void Setup();

	// update the game screen every frame
	void Update(CustomEvent event);

	// draw things on the screen
	void Draw();

	// process the mouse and perform appropriate actions
	void ProcessMouse(sf::Event event);
#pragma endregion SceneRequired

#pragma region GameAccess
	// access the score from the game
	int GetScore();

	// access the deck size from the game
	int GetCardsLeft();

	// reset the game
	void ResetGame();
#pragma endregion GameAccess

private:
	Game* game;

	// process the left mouse button
	void processLMBClicked(sf::Vector2f mousePos);

	// process the mouse movement
	void processMouseMoved(sf::Vector2f mousePos);
};

