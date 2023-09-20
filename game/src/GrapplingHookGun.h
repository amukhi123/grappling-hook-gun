#pragma once

#include <vector>

#include "IGameBase.h"

namespace GrapplingHookGunProperties
{
	inline constexpr float LINE_WIDTH {100.f};
};

class GrapplingHookGun
{
public:
	GrapplingHookGun(const std::vector<BoundingBox>& BoundingBoxes);

	void Shoot(const Vector3& Origin, const Vector3& Direction) const;

	void AddBoundingBoxes(const std::vector<BoundingBox>& BoundingBoxes);
private:
	std::vector<BoundingBox> m_BoundingBoxes {};
};
