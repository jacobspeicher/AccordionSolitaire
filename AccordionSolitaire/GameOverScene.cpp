#include "GameOverScene.h"

GameOverScene::GameOverScene(sf::RenderWindow& window) : Scene(window)
{
	gameOverUI = new GameOverUI(window);
	backCard = new Card();

	finalScore = 0;
	stackedPoints = 0;
	bonus = 0;
	movingPenalty = 0;
	penalty = 0;

	Setup();
}

#pragma region SceneRequired
void GameOverScene::Setup()
{
	if (!font.loadFromFile("Assets/Fonts/Accordion.otf")) {}

	text["finalScore"] = new sf::Text();
	text["metrics"] = new sf::Text();

	std::map<std::string, sf::Text*>::iterator itr;
	for (itr = text.begin(); itr != text.end(); ++itr)
	{
		itr->second->setFont(font);
		itr->second->setFillColor(sf::Color::Black);
	}

	text["finalScore"]->setCharacterSize(22);
	text["metrics"]->setCharacterSize(18);

	sf::Vector2f cardPos(window->getSize().x / 2, window->getSize().y / 2);

	text["finalScore"]->setPosition(sf::Vector2f(cardPos.x - 200, cardPos.y - 100));
	text["metrics"]->setPosition(sf::Vector2f(cardPos.x - 200, cardPos.y - 50));

	backCard->sprite.setPosition(cardPos);
	backCard->sprite.setRotation(90);
	backCard->sprite.setScale(sf::Vector2f(2, 2));
}

void GameOverScene::Update(CustomEvent event)
{
	Draw();
	gameOverUI->Draw();

	if (event.screen == Screen::GameOver)
	{
		CustomEvent* changeScreen;
		switch (static_cast<GameOverEvents>(event.event))
		{
		case GameOverEvents::SettleScore:
			setScoreMetrics(event.data);
			break;
		case GameOverEvents::Quit:
			window->close();
			break;
		case GameOverEvents::ReturnToMainMenu:
			changeScreen = new CustomEvent(Screen::Global, static_cast<int>(GlobalEvents::ReturnToMenu));
			EventManager::QueueEvent(*changeScreen);
			break;
		case GameOverEvents::ResetGame:
			changeScreen = new CustomEvent(Screen::Global, static_cast<int>(GlobalEvents::PlayGame));
			CustomEvent resetGame(Screen::Play, static_cast<int>(PlayEvents::ResetGame));
			EventManager::QueueEvent(*changeScreen);
			EventManager::QueueEvent(resetGame);
			break;
		}
	}
}

void GameOverScene::Draw()
{
	window->draw(backCard->sprite);

	std::map<std::string, sf::Text*>::iterator itr;
	for (itr = text.begin(); itr != text.end(); ++itr)
	{
		window->draw(*itr->second);
	}
}

void GameOverScene::ProcessMouse(sf::Event event)
{
	gameOverUI->ProcessMouse(event);
}
#pragma endregion SceneRequired

#pragma region private
void GameOverScene::setScoreMetrics(std::map<std::string, int> scoreMap)
{
	finalScore = scoreMap["finalScore"];
	stackedPoints = scoreMap["stackedPoints"];
	bonus = scoreMap["bonus"];
	movingPenalty = scoreMap["movingPenalty"];
	penalty = scoreMap["penalty"];

	text["finalScore"]->setString("Final Score : " + std::to_string(finalScore));

	std::string metrics = "Stacking Points : " + std::to_string(stackedPoints) + "\n";
	metrics += "Bonus Points : " + std::to_string(bonus) + "\n";
	metrics += "Moving Penalty : " + std::to_string(-1 * movingPenalty) + "\n";
	metrics += "Unstacked Penalty : " + std::to_string(-1 * penalty);
	text["metrics"]->setString(metrics);
}
#pragma endregion private
