#pragma once

namespace GameProperties
{
	enum class GameObjects : int
	{
		Environment = 0,
		Player = 1
	};
};

class Game
{
public:
	Game();

	~Game();

	void GameLoop() const;
};
