#pragma once

enum class Screen {
	null,
	Global,
	MainMenu,
	Instructions,
	Options,
	Play,
	GameOver,
};

enum class GlobalEvents {
	PlayGame,
	GameOver,
	ReturnToMenu,
	Quit,
};

enum class MainMenuEvents {
	OpenInstructions,
	OpenOptions,
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
