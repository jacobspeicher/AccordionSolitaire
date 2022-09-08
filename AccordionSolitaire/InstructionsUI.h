#pragma once
#include "UserInterface.h"
#include "Card.h"

class InstructionsUI :
    public UserInterface
{
public:
    // constructor
    InstructionsUI(sf::RenderWindow& window);

#pragma region UserInterfaceRequired
    // set up the instructions UI
    void Setup();

    // draw the instructions UI
    void Draw();
#pragma endregion UserInterfaceRequired

private:
    sf::Texture deckTexture;
    sf::Sprite deckPile;

    sf::Texture arrowTexture;
    sf::Sprite arrow;

    Card* ace_clubs = new Card(1, 0);
    Card* ace_diamonds = new Card(1, 1);
    Card* jack_spades = new Card(11, 3);
    Card* five_spades = new Card(5, 3);
    Card* blank_card = new Card(0, 0);
};

