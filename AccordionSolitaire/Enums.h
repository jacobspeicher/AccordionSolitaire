#pragma once

enum class Screen {
	MainMenu,
	Instructions,
	Options,
	Play,
	GameOver,
};

enum class CustomEventTypes {
	null,
	ChangeScene,
};

enum class MainMenuEvents {
	OpenInstructions,
	OpenOptions,
	PlayGame,
	Quit,
};

enum class InstructionsEvents {

};

enum class OptionsEvents {

};

enum class PlayEvents {

};

enum class GameOverEvents {
	ReturnToMainMenu,
	ResetGame,
	Quit,
};
