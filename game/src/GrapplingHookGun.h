#pragma once

#include <vector>

#include "IGameBase.h"
#include "PlayerProperties.h"

namespace GrapplingHookGunProperties
{
	inline constexpr float LINE_WIDTH {100.f};
	inline constexpr float GRAPPLE_SPEED {20.f};
};

class GrapplingHookGun
{
public:
	GrapplingHookGun(const std::vector<BoundingBox>& BoundingBoxes);

	Vector3& Shoot(const Vector3& Origin, const Vector3& Direction, PlayerProperties::PlayerStates& OutPlayerState);

	void AddBoundingBoxes(const std::vector<BoundingBox>& BoundingBoxes);
private:
	std::vector<BoundingBox> m_BoundingBoxes {};

	Vector3 m_HitPoint {};

	Vector3 MoveTowards(const Vector3& Source, const Vector3& Destination);

	Vector3 BeginGrapple(const Vector3& Origin, const Vector3& HitPoint);

	Vector3 EndGrapple();

	Vector3 HitPoint(const Vector3& Origin, const Vector3& Direction);
};
