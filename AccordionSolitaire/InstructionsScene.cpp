#include "InstructionsScene.h"

InstructionsScene::InstructionsScene(sf::RenderWindow& window) : Scene(window)
{
	Setup();
}

#pragma region SceneRequired
void InstructionsScene::Setup()
{
	instructionsUI = new InstructionsUI(*window);
}

void InstructionsScene::Update(CustomEvent event)
{
	Draw();

	if (event.screen == Screen::Instructions)
	{
		CustomEvent* instructionsEvent = new CustomEvent();

		switch (static_cast<InstructionsEvents>(event.event))
		{
		case InstructionsEvents::ReturnToMenu:
			instructionsEvent = new CustomEvent(Screen::Global, static_cast<int>(GlobalEvents::ReturnToMenu));
			break;
		}

		EventManager::QueueEvent(*instructionsEvent);
	}
}

void InstructionsScene::Draw()
{
	instructionsUI->Draw();
}

void InstructionsScene::ProcessMouse(sf::Event event)
{
	instructionsUI->ProcessMouse(event);
}
#pragma endregion SceneRequired