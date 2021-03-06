#include "Stack.h"


Stack::Stack(const std::vector<Card>& vCards, sf::Vector2f vStackPosition, int idx, std::string sFontName)
{
	index = idx;
	size = vCards.size();
	cards = vCards;
	stackPosition = vStackPosition;
	fontName = sFontName;

	if (!baseStackTexture.loadFromFile("Assets/Cards/0c.png")) {}
}

void Stack::SetTexturePath()
{
	if (cards.size() > 0)
	{
		texturePath = cards.back().getTexturePath();
		return;
	}

	texturePath = "Assets/Cards/0c.png";
}

void Stack::SetSizeText()
{
	if (!font.loadFromFile(fontName)) {}

	sizeText.setFont(font);
	sizeText.setCharacterSize(10);
	sizeText.setFillColor(sf::Color::Black);
	sizeText.setString(std::to_string(cards.size()));
	sizeText.setPosition(sf::Vector2f(stackPosition.x - 60, stackPosition.y + 75));
	sizeText.setStyle(sf::Text::Bold);
}

void Stack::CreateSprite()
{
	SetTexturePath();
	SetSizeText();
	if (!baseStackTexture.loadFromFile(texturePath)) {}

	baseStackSprite.setTexture(baseStackTexture);
	localCenter = sf::Vector2f(baseStackSprite.getLocalBounds().width / 2, baseStackSprite.getLocalBounds().height / 2);
	baseStackSprite.setOrigin(localCenter);
	baseStackSprite.setPosition(stackPosition);
	baseStackSprite.setScale(sf::Vector2f(0.75, 0.75));
}

void Stack::DrawStack(sf::RenderWindow& window, sf::Shader& shader)
{
	window.draw(baseStackSprite, &shader);
	window.draw(sizeText);
}

void Stack::DrawStack(sf::RenderWindow& window, sf::Vector2f pos, sf::Shader& shader)
{
	sf::Vector2f origin = baseStackSprite.getOrigin();
	sf::Vector2f textOffset;
	textOffset.x = (origin.x - localCenter.x) * float(0.75) + 60;
	textOffset.y = (localCenter.y - origin.y) * float(0.75) + 75;
	sizeText.setPosition(sf::Vector2f(pos.x - textOffset.x, pos.y + textOffset.y));

	baseStackSprite.setPosition(pos);
	window.draw(baseStackSprite, &shader);
	window.draw(sizeText);
}

void Stack::AddCardToStack(Card card)
{
	cards.push_back(card);
	//std::cout << "Stack:" << std::endl;
	//for (int i = 0; i < cards.size(); ++i)
	//{
	//	std::cout << i << " : " << cards[i].value << ", " << cards[i].suit << std::endl;
	//}
	//std::cout << std::endl;
}

void Stack::ResetStackPosition()
{
	baseStackSprite.setPosition(stackPosition);
	SetSizeText();
}

void Stack::ResetStackOrigin()
{
	baseStackSprite.setOrigin(localCenter);
}

// getters
sf::Vector2f Stack::getStackPosition()
{
	return stackPosition;
}

bool Stack::getEnabled()
{
	return enabled;
}

std::vector<Card> Stack::getCards()
{
	return cards;
}

sf::Sprite Stack::getBaseStackSprite()
{
	return baseStackSprite;
}

int Stack::getIndex()
{
	return index;
}

int Stack::getSize()
{
	return cards.size();
}

Card Stack::getTopCard()
{
	return cards.back();
}

// setters
void Stack::setStackPosition(sf::Vector2f vStackPosition)
{
	stackPosition = vStackPosition;
}

void Stack::setEnabled(bool bEnabled)
{
	enabled = bEnabled;
}

void Stack::setSpriteOrigin(sf::Vector2f pos)
{
	baseStackSprite.setOrigin(pos);
}

void Stack::setIndex(int idx)
{
	index = idx;
}
