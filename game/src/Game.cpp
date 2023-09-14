#include "Game.h"
#include "raylib.h"

Game::Game() : m_Camera {}
{
	constexpr int WINDOW_WIDTH {1920};
	constexpr int WINDOW_HEIGHT {1080};

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Grappling Hook Gun");

	DisableCursor();
}

Game::~Game()
{
	CloseWindow();
}

void Game::GameLoop() const
{
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);

		DrawFPS(0, 0);

		EndDrawing();
	}
}
