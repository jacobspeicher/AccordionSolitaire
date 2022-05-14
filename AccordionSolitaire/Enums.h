#pragma once

enum class Screen {
	null,
	MainMenu,
	Instructions,
	Options,
	Play,
	GameOver,
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
	ResetGame,
};

enum class GameOverEvents {
	ReturnToMainMenu,
	ResetGame,
	Quit,
};
