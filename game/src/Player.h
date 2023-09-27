#pragma once

#include "IGameBase.h"
#include "PlayerProperties.h"
#include "Debug.h"
#include "GrapplingHookGun.h"

class Player : public IGameBase, public Debug
{
public:
	Player(const Vector2& PlayerSpawnPosition, const Vector2& CubeSize, const std::vector<BoundingBox>& EnvironmentBoundingBoxes);

	void Update() override;

	Camera3D& Camera();

	void AttachGun(const GrapplingHookGun& Gun);

	bool IsColliding();
protected:
	void DebugActions() override;
private:
	Camera3D m_Camera {};

	GrapplingHookGun m_GrapplingHookGun {{}};

	PlayerProperties::PlayerStates m_CurrentPlayerState {};

	std::vector<BoundingBox> m_EnvironmentBoundingBoxes {};

	Vector3 Movement() const;

	Vector3 Rotation() const;

	BoundingBox GenerateBoundingBox();

	void RequestShot();

	void RequestMovement();

	void Shoot();

	void Fall();
};
