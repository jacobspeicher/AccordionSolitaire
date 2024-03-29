#include "Deck.h"

Deck::Deck(bool bJoker, sf::Vector2f vLocDeck)
{
	deckBack = "Assets/SaraCards/back.png";
	locDeck = vLocDeck;
	SetDeckSprite();

	int suit = -1;
	for (int i = 0; i < 52; ++i) 
	{
		int value = i % 13 + 1;
		if (i % 13 == 0)
		{
			++suit;
		}
		Card newCard(value, suit);
		initialDeck.push_back(newCard);
		//std::cout << value << ", " << suit << std::endl;
	}
	Shuffle();
}

void Deck::Shuffle()
{
	srand(time(0));
	for (int upperBound = 52; upperBound > 0; --upperBound)
	{
		int cardIdx = rand() % upperBound;
		//std::cout << cardIdx << std::endl;
		cards.push_back(initialDeck[cardIdx]);
		//std::cout << upperBound << " : " << initialDeck[cardIdx].value << ", " << initialDeck[cardIdx].suit << std::endl;
		initialDeck.erase(initialDeck.begin() + cardIdx);
	}
}

void Deck::DrawDeckPile(sf::RenderWindow& window, sf::Shader& shader)
{
	window.draw(deckPile, &shader);
}

void Deck::DrawCard()
{
	cards.pop_back();
	if (cards.size() == 0)
	{
		DeckIsEmpty();
	}
}

// private

void Deck::SetDeckSprite()
{
	if (!deckTexture.loadFromFile(deckBack)) {}
	deckPile.setTexture(deckTexture);
	deckPile.setOrigin(sf::Vector2f(deckPile.getLocalBounds().width / 2, deckPile.getLocalBounds().height / 2));
	deckPile.setScale(sf::Vector2f(0.75, 0.75));

	deckPile.setPosition(locDeck);
}

void Deck::DeckIsEmpty()
{
	deckBack = "Assets/Cards/0c.png";
	//locDeck = sf::Vector2f(1000.0f, 1000.0f);
	SetDeckSprite();
}
