#pragma once

#include <memory>

struct Camera3D;

namespace GameProperties
{
	inline constexpr int WINDOW_WIDTH {1000};
	inline constexpr int WINDOW_HEIGHT {1000};

	inline constexpr float FOV {45.f};
};

class Game
{
public:
	Game();

	~Game();

	void GameLoop() const;

private:
	std::unique_ptr<Camera3D> m_Camera {};
};
