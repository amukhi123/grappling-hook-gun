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
	
	gameObjects.push_back(std::make_shared<Environment>());

	if (std::shared_ptr<Environment> environment {std::dynamic_pointer_cast<Environment>(gameObjects[static_cast<int>(GameProperties::GameObjects::Environment)])})
	{
		gameObjects.push_back(std::make_shared<Player>(environment->MapSize(), environment->CubeSize()));
	
		std::vector<std::shared_ptr<IBase>> userInterfaceObjects {};
	
		userInterfaceObjects.push_back(std::make_shared<Crosshair>());
	
		if (std::shared_ptr<Player> player {std::dynamic_pointer_cast<Player>(gameObjects[static_cast<int>(GameProperties::GameObjects::Player)])})
		{
			userInterfaceObjects.push_back(std::make_shared<PlayerDebugUserInterface>(player));

			Camera& cam {player->Camera()};

			GrapplingHookGun grapplingHookGun {environment->BoundingBoxes()};	
			player->AttachGun(grapplingHookGun);

			while (!WindowShouldClose())
			{
				BeginDrawing();
		
				ClearBackground(WHITE);
	
				BeginMode3D(player->Camera());

				const Vector3 oldPlayerPosition {cam.position};	
				const Vector3 oldTargetPosition {cam.target};

				for (int i {0}; i < gameObjects.size(); ++i)
				{
					gameObjects[i]->Update();
				}

				if (environment->CheckCollisions(player->GeneratePlayerBoundingBox()))
				{
					cam.position = oldPlayerPosition;
					cam.target = oldTargetPosition;
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
}
