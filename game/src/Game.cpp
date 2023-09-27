#include <vector>
#include <memory>

#include "Game.h"
#include "raylib.h"
#include "Enviornment.h"
#include "Player.h"
#include "IBase.h"
#include "Crosshair.h"
#include "PlayerDebugUserInterface.h"

Game::Game()
{
	constexpr int WINDOW_WIDTH {1920};
	constexpr int WINDOW_HEIGHT {1080};

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Grappling Hook Gun");

	ToggleFullscreen();

	DisableCursor();
}

Game::~Game()
{
	CloseWindow();
}

void Game::GameLoop() const
{
	std::vector<std::shared_ptr<IBase>> gameObjects {};
	
	gameObjects.push_back(std::make_shared<Environment>());

	if (std::shared_ptr<Environment> environment {std::dynamic_pointer_cast<Environment>(gameObjects[static_cast<int>(GameProperties::GameObjects::Environment)])})
	{
		gameObjects.push_back(std::make_shared<Player>(environment->PlayerSpawnPosition(), environment->CubeSize(), environment->BoundingBoxes()));
	
		std::vector<std::shared_ptr<IBase>> userInterfaceObjects {};
	
		userInterfaceObjects.push_back(std::make_shared<Crosshair>());
	
		if (std::shared_ptr<Player> player {std::dynamic_pointer_cast<Player>(gameObjects[static_cast<int>(GameProperties::GameObjects::Player)])})
		{
			userInterfaceObjects.push_back(std::make_shared<PlayerDebugUserInterface>(player));

			Camera& cam {player->Camera()};

			GrapplingHookGun grapplingHookGun {environment->BoundingBoxes()};	

			player->AttachGun(grapplingHookGun);

			constexpr int fpsTextPosition {10};

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

				DrawFPS(fpsTextPosition, fpsTextPosition);
		
				EndDrawing();
			}
		}
	}
}
