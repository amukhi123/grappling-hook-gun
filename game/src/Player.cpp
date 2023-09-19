#include "Player.h"
#include "Enviornment.h"
#include "rcamera.h"

Player::Player(const Vector2& MapSize, const Vector2& CubeSize) : m_Camera {Camera3D {{MapSize.y / 2, CubeSize.x, MapSize.x / 2}, Vector3Add(Camera().position, GetCameraForward(&Camera())), VectorConstants::UP_VECTOR, PlayerProperties::PLAYER_FOV, CAMERA_PERSPECTIVE}}
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
