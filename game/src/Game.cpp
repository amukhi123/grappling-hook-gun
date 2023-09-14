#include <vector>

#include "Game.h"
#include "raylib.h"
#include "Enviornment.h"

Game::Game() : m_Camera {std::make_unique<Camera3D>(Camera3D{{0.f, 10.f, 10.f}, VectorConstants::ZERO_VECTOR, VectorConstants::UP_VECTOR, GameProperties::FOV, CAMERA_PERSPECTIVE})}
{
	InitWindow(GameProperties::WINDOW_WIDTH, GameProperties::WINDOW_HEIGHT, "Grappling Hook Gun");

	DisableCursor();
}

Game::~Game()
{
	CloseWindow();
}

void Game::GameLoop() const
{
	std::vector<std::unique_ptr<IGameBase>> gameObjects {};

	gameObjects.push_back(std::make_unique<Environment>());

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);

		if (m_Camera)
		{ 
			BeginMode3D(*m_Camera);

			for (int i {0}; i < gameObjects.size(); ++i)
			{
				gameObjects[i]->Update();
			}

			EndMode3D();
		}
		else
		{
			constexpr int FONT_SIZE {10};

			DrawText("Camera Creation Failed", GameProperties::WINDOW_WIDTH / 2, GameProperties::WINDOW_HEIGHT / 2, FONT_SIZE, BLACK); 
		}

		DrawFPS(0, 0);

		EndDrawing();
	}
}
