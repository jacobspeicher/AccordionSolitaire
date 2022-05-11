#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Card.h"

class Deck
{
public:
	bool joker;
	std::vector<Card> cards;

	std::string deckBack;
	sf::Texture deckTexture;
	sf::Sprite deckPile;
	sf::Vector2f locDeck;

	// create a deck with 52 cards
	// if the game is set to include a joker, the deck will have 53 cards
	Deck(bool bJoker, sf::Vector2f vLocDeck);

	// draw the deck pile
	void DrawDeckPile(sf::RenderWindow& window, sf::Shader& shader);

	// shuffle the deck
	void Shuffle();
	
	// draw a card from the deck
	Card& DrawCard();

private:
	std::vector<Card> initialDeck;

	// set the deck's texture and setup the sprite
	void SetDeckSprite();

	// the deck is empty, change the deck back to "blank"
	void DeckIsEmpty();
};

