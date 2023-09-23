#include "Player.h"
#include "rcamera.h"

Player::Player(const Vector2& MapSize, const Vector2& CubeSize) : m_Camera {Camera3D {{MapSize.y / 2, CubeSize.x + PlayerProperties::PLAYER_SIZE / 2, MapSize.x / 2}, Vector3Add(Camera().position, GetCameraForward(&Camera())), VectorConstants::UP_VECTOR, PlayerProperties::PLAYER_FOV, CAMERA_PERSPECTIVE}}, m_GrapplingHookGun {{}}, m_CurrentPlayerState {PlayerProperties::PlayerStates::Default}
{
}

void Player::Update()
{
	switch (m_CurrentPlayerState)
	{
		case PlayerProperties::PlayerStates::Default:
			UpdateCameraPro(&Camera(), Movement(), Rotation(), 0.f); 
			RequestShot();
			break;
		case PlayerProperties::PlayerStates::Grapple:
		case PlayerProperties::PlayerStates::InAir:
			Shoot();
			break;
		case PlayerProperties::PlayerStates::Falling:
			// Implement gravity
			break;
	}

	CheckDebugActions();
}

Camera3D& Player::Camera() 
{
	return m_Camera;
}

Vector3 Player::Movement() const
{
	Vector3 movementVector {Vector3Zero()};

	float movementSpeed {0.f};

	if (IsKeyDown(KEY_LEFT_SHIFT))
	{
		movementSpeed = PlayerProperties::PLAYER_SPRINT_SPEED;
	}
	else
	{
		movementSpeed = PlayerProperties::PLAYER_MOVEMENT_SPEED;
	}

	movementSpeed *= GetFrameTime();

	if (IsKeyDown(KEY_W))
	{
		movementVector.x += movementSpeed;
	}

	if (IsKeyDown(KEY_S))
	{
		movementVector.x -= movementSpeed;
	}

	if (IsKeyDown(KEY_D))
	{
		movementVector.y += movementSpeed;
	}

	if (IsKeyDown(KEY_A))
	{
		movementVector.y -= movementSpeed;
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

BoundingBox Player::GeneratePlayerBoundingBox()
{
	const float halfPlayerSize {PlayerProperties::PLAYER_SIZE / 2};

	const Vector3 halfPlayerSizeVector {halfPlayerSize, halfPlayerSize, halfPlayerSize};
	const Vector3 bottomLeftPlayerPosition {Vector3Subtract(Camera().position, halfPlayerSizeVector)};
	const Vector3 topRightPlayerPosition {PlayerProperties::PLAYER_SIZE, PlayerProperties::PLAYER_SIZE, PlayerProperties::PLAYER_SIZE};

	const BoundingBox playerBoundingBox {bottomLeftPlayerPosition, Vector3Add(bottomLeftPlayerPosition, topRightPlayerPosition)};

	return playerBoundingBox;
}

void Player::DebugActions()
{
	DrawBoundingBox(GeneratePlayerBoundingBox(), DebugProperties::DEBUG_COLOUR);

	DrawSphere(Camera().target, DebugProperties::SPHERE_RADIUS, DebugProperties::DEBUG_COLOUR);
}

void Player::AttachGun(const GrapplingHookGun& Gun)
{
	m_GrapplingHookGun = Gun;
}

void Player::RequestShot()
{
	if (IsKeyDown(KEY_E))
	{
		m_CurrentPlayerState = PlayerProperties::PlayerStates::Grapple;
	}
}

void Player::Shoot()
{
	Camera3D& player {Camera()};

	const Vector3 relativeTargetPosition {Vector3Subtract(m_Camera.target, m_Camera.position)};

	player.position = m_GrapplingHookGun.Shoot(m_Camera.position, Vector3Normalize(relativeTargetPosition), m_CurrentPlayerState);

	player.target = Vector3Add(player.position, relativeTargetPosition);
}
