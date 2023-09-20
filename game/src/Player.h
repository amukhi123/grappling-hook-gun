#pragma once

#include "IGameBase.h"
#include "Debug.h"
#include "GrapplingHookGun.h"

class Player : public IGameBase, public Debug
{
public:
	Player(const Vector2& MapSize, const Vector2& CubeSize);

	void Update() override;

	Camera3D& Camera();

	BoundingBox GeneratePlayerBoundingBox();

	void AttachGun(const GrapplingHookGun& Gun);
protected:
	void DebugActions() override;

private:
	Camera3D m_Camera {};

	GrapplingHookGun m_GrapplingHookGun {{}};

	Vector3 Movement() const;

	Vector3 Rotation() const;

	void Shoot() const;
};
