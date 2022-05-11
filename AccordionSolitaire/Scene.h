#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
public:
	// constructor
	Scene(sf::RenderWindow& inWindow);

	virtual void Setup() = 0;
	virtual void Draw() = 0;
	virtual void ProcessMouse(sf::Event event) = 0;

protected:
	sf::Font font;
	std::map<std::string, sf::Shader*> shaders;
	std::map<std::string, sf::Text*> text;
	sf::RenderWindow* window;
};

