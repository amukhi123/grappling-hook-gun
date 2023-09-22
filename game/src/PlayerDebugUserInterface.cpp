#include "PlayerDebugUserInterface.h"
#include "Debug.h"
#include "Player.h"

PlayerDebugUserInterface::PlayerDebugUserInterface(const std::shared_ptr<Player>& PlayerCharacter) : m_Player {PlayerCharacter}
{
}

void PlayerDebugUserInterface::Update()
{
	DrawPlayerPosition();
}

void PlayerDebugUserInterface::DrawPlayerPosition()
{
	const Vector3 playerPosition {m_Player->Camera().position};

	const float TEXT_X {GetScreenWidth() - (GetScreenWidth() / 5.f)};
	const float TEXT_Y {20.f};

	DrawText(TextFormat("X: %f\n\nY: %f\n\nZ: %f", playerPosition.x, playerPosition.y, playerPosition.z), TEXT_X, TEXT_Y, DebugProperties::FONT_SIZE, DebugProperties::TEXT_COLOUR);
}
