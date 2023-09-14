#pragma once

#include <memory>

class Camera3D;

class Game
{
public:
	Game();

	~Game();

	void GameLoop() const;

private:
	std::unique_ptr<Camera3D> m_Camera {};
};
