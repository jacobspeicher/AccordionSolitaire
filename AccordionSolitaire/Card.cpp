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
	texturePath = "Assets/Cards/" + std::to_string(value) + static_cast<char>(Suit[suit]) + ".png";
}

void Card::CreateSprite()
{
	SetTexturePath();
	if (!cardTexture.loadFromFile(texturePath))
	{
		//std::cout << "ERROR: Card texture failed to load at " << texturePath << std::endl;
	}

	sprite.setTexture(cardTexture);
	sprite.setOrigin(sf::Vector2f(75, 125));
}

void Card::DrawOnScreen(sf::RenderWindow& window, sf::Vector2f position, sf::Shader& shader)
{
	sprite.setPosition(position);
	window.draw(sprite, &shader);
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
