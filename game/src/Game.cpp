#include <vector>
#include <memory>

#include "Game.h"
#include "raylib.h"
#include "Enviornment.h"
#include "Player.h"
#include "IBase.h"
#include "Crosshair.h"

Game::Game()
{
	constexpr int WINDOW_WIDTH {1000};
	constexpr int WINDOW_HEIGHT {1000};

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Grappling Hook Gun");

	DisableCursor();
}

Game::~Game()
{
	CloseWindow();
}

void Game::GameLoop() const
{
	std::vector<std::shared_ptr<IBase>> gameObjects {};
	std::vector<std::shared_ptr<IBase>> userInterfaceObjects {};
	
	gameObjects.push_back(std::make_shared<Player>());
	gameObjects.push_back(std::make_shared<Environment>());

	userInterfaceObjects.push_back(std::make_shared<Crosshair>());

	if (std::shared_ptr<Player> player {std::dynamic_pointer_cast<Player>(gameObjects[static_cast<int>(GameProperties::GameObjects::Player)])})
	{
		Camera cam {player->Camera()};
	
		while (!WindowShouldClose())
		{
			BeginDrawing();
	
			ClearBackground(WHITE);
	

			BeginMode3D(player->Camera());
	
			for (int i {0}; i < gameObjects.size(); ++i)
			{
				gameObjects[i]->Update();
			}

			EndMode3D();

			for (int i {0}; i < userInterfaceObjects.size(); ++i)
			{
				userInterfaceObjects[i]->Update();
			}

			DrawFPS(0, 0);
	
			EndDrawing();
		}
	}
}
