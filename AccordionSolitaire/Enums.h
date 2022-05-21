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
	PlayGame,
	OpenInstructions,
	OpenOptions,
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
	SettleScore,
	ReturnToMainMenu,
	ResetGame,
	Quit,
};
