#pragma once

#include "IGameBase.h"

namespace PlayerProperties
{
	inline constexpr float PLAYER_FOV {45.f};
}

class Player : public IGameBase
{
public:
	Player();

	void Update() override;

	Camera3D& Camera();

private:
	Vector3 m_PlayerPosition {};

	Camera3D m_Camera {};
};
