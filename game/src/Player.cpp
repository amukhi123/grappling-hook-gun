#include "Player.h"

Player::Player() : m_PlayerPosition {1.f, 0.5f, 1.f}, m_Camera {Camera3D {m_PlayerPosition, {5.f, 0.f, 5.f}, VectorConstants::UP_VECTOR, PlayerProperties::PLAYER_FOV, CAMERA_PERSPECTIVE}}
{
}

void Player::Update()
{
	UpdateCameraPro(&Camera(), Movement(), Rotation(), 0.f); 
}

Camera3D& Player::Camera() 
{
	return m_Camera;
}

Vector3 Player::Movement() const
{
	Vector3 movementVector {Vector3Zero()};

	if (IsKeyDown(KEY_W))
	{
		movementVector.x += PlayerProperties::PLAYER_MOVEMENT_SPEED * GetFrameTime();
	}

	if (IsKeyDown(KEY_S))
	{
		movementVector.x -= PlayerProperties::PLAYER_MOVEMENT_SPEED * GetFrameTime();
	}

	if (IsKeyDown(KEY_D))
	{
		movementVector.y += PlayerProperties::PLAYER_MOVEMENT_SPEED * GetFrameTime();
	}

	if (IsKeyDown(KEY_A))
	{
		movementVector.y -= PlayerProperties::PLAYER_MOVEMENT_SPEED * GetFrameTime();
	}

	return movementVector;
}

Vector3 Player::Rotation() const
{
	Vector3 rotationVector {Vector3Zero()};

	if (IsKeyDown(KEY_UP))
	{
		rotationVector.y -= PlayerProperties::PLAYER_ROTATION_SPEED * GetFrameTime();
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		rotationVector.y += PlayerProperties::PLAYER_ROTATION_SPEED * GetFrameTime();
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		rotationVector.x += PlayerProperties::PLAYER_ROTATION_SPEED * GetFrameTime();
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		rotationVector.x -= PlayerProperties::PLAYER_ROTATION_SPEED * GetFrameTime();
	}

	return rotationVector;
}
