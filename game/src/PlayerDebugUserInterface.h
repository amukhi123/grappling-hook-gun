#pragma once

#include <memory>

#include "IUserInterfaceBase.h"

class Player;

class PlayerDebugUserInterface : public IUserInterfaceBase
{
public:
	PlayerDebugUserInterface(const std::shared_ptr<Player>& PlayerCharacter);

	void Update() override;
private:
	std::shared_ptr<Player> m_Player {};

	void DrawPlayerPosition();
};
