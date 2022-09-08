#include "Card.h"

Card::Card()
{
	value = 0;
	suit = 0;
	CreateSprite();
}

Card::Card(int iValue, int iSuit)
{
	value = iValue;
	suit = iSuit;
}

void Card::SetTexturePath()
{
	texturePath = "Assets/SaraCards/" + std::to_string(value) + static_cast<char>(Suit[suit]) + ".png";
}

void Card::CreateSprite()
{
	SetTexturePath();
	if (!cardTexture.loadFromFile(texturePath))
	{
		//std::cout << "ERROR: Card texture failed to load at " << texturePath << std::endl;
	}

	sprite.setTexture(cardTexture);
	localCenter = sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setOrigin(localCenter);
	sprite.setScale(sf::Vector2f(0.75, 0.75));

	//std::cout << sprite.getGlobalBounds().width << ", " << sprite.getGlobalBounds().height << std::endl;
}

void Card::DrawOnScreen(sf::RenderWindow& window, sf::Vector2f position, sf::Shader& shader)
{
	sprite.setPosition(position);
	window.draw(sprite, &shader);
}

void Card::ResetCenter()
{
	sprite.setOrigin(localCenter);
}

// getter/setter
void Card::setTexturePath(std::string sTexturePath)
{
	texturePath = sTexturePath;
}

std::string Card::getTexturePath()
{
	return texturePath;
}

