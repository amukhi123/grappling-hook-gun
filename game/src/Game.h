#pragma once

namespace GameProperties
{
	// TODO: remove these and use height and width accessor functions
	inline constexpr int WINDOW_WIDTH {1000};
	inline constexpr int WINDOW_HEIGHT {1000};

	enum class GameObjects : int
	{
		Player = 0
	};
};

class Game
{
public:
	Game();

	~Game();

	void GameLoop() const;
};
