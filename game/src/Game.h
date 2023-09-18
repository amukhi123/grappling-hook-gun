#pragma once

namespace GameProperties
{
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
