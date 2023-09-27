#include <limits>

#include "GrapplingHookGun.h"
#include "Debug.h"

GrapplingHookGun::GrapplingHookGun(const std::vector<BoundingBox>& BoundingBoxes) : m_BoundingBoxes {BoundingBoxes}, m_HitPoint {}
{
}

Vector3& GrapplingHookGun::Shoot(const Vector3& Origin, const Vector3& Direction, PlayerProperties::PlayerStates& OutPlayerState)
{
	if (OutPlayerState == PlayerProperties::PlayerStates::Grapple)
	{
		m_HitPoint = HitPoint(Origin, Direction);

		OutPlayerState = PlayerProperties::PlayerStates::InAir;
	}

	if (Vector3Distance(m_HitPoint, Origin) < PlayerProperties::PLAYER_SIZE)
	{
		OutPlayerState = PlayerProperties::PlayerStates::Falling;
	}

	return BeginGrapple(Origin, m_HitPoint);
}

void GrapplingHookGun::AddBoundingBoxes(const std::vector<BoundingBox>& BoundingBoxes)
{
	if (m_BoundingBoxes.size() == 0)
	{
		m_BoundingBoxes = BoundingBoxes;
	}
}

Vector3 GrapplingHookGun::MoveTowards(const Vector3& Source, const Vector3& Destination)
{
	const Vector3 movementVector {Vector3Normalize(Vector3Subtract(Destination, Source))};

	const float speedModifier {GrapplingHookGunProperties::GRAPPLE_SPEED * GetFrameTime()};

	const Vector3 speedVector {VectorHelpers::Vector3FromFloat(speedModifier)};
	const Vector3 adjustedMovementVector {Vector3Multiply(movementVector, speedVector)};

	return Vector3Add(Source, adjustedMovementVector);
}

Vector3 GrapplingHookGun::BeginGrapple(const Vector3& Origin, const Vector3& HitPoint)
{
	constexpr Vector3 grappleGunOffset {0.f, 0.3f, 0.f};

	DrawCapsule(Vector3Subtract(Origin, grappleGunOffset), HitPoint, DebugProperties::CAPSULE_RADIUS, DebugProperties::CAPSUPLE_SLICES, DebugProperties::CAPSULE_RINGS, DebugProperties::DEBUG_COLOUR);

	return MoveTowards(Origin, HitPoint);
}

Vector3 GrapplingHookGun::HitPoint(const Vector3& Origin, const Vector3& Direction)
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

	return closestRayCollision.point;
}
