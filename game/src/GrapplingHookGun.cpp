#include <limits>

#include "GrapplingHookGun.h"
#include "rlgl.h"
#include "Debug.h"

GrapplingHookGun::GrapplingHookGun(const std::vector<BoundingBox>& BoundingBoxes) : m_BoundingBoxes {BoundingBoxes}
{
}

void GrapplingHookGun::Shoot(const Vector3& Origin, const Vector3& Direction) const
{
	Ray ray {Origin, Direction};
	RayCollision closestRayCollision {false, std::numeric_limits<float>::max(), Vector3Zero(), Vector3Zero()};

	for (const BoundingBox& boundingBox : m_BoundingBoxes)
	{
		RayCollision currentRayCollision {GetRayCollisionBox(ray, boundingBox)};

		if (currentRayCollision.hit && currentRayCollision.distance < closestRayCollision.distance)
		{
			closestRayCollision = currentRayCollision;
		}
	}

	rlSetLineWidth(GrapplingHookGunProperties::LINE_WIDTH);

	DrawLine3D(Origin, closestRayCollision.point, DebugProperties::DEBUG_COLOUR);
}

void GrapplingHookGun::AddBoundingBoxes(const std::vector<BoundingBox>& BoundingBoxes)
{
	if (m_BoundingBoxes.size() == 0)
	{
		m_BoundingBoxes = BoundingBoxes;
	}
}
