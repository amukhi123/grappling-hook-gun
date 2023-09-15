#include <vector>
#include <memory>

#include "Game.h"
#include "raylib.h"
#include "Enviornment.h"
#include "Player.h"

Game::Game()
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
	std::vector<std::shared_ptr<IGameBase>> gameObjects {};
	
	gameObjects.push_back(std::make_shared<Player>());
	gameObjects.push_back(std::make_shared<Environment>());


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
	
			DrawFPS(0, 0);
	
			EndDrawing();
		}
	}
}
