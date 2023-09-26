#include <vector>

#include "Player.h"
#include "rcamera.h"

Player::Player(const Vector2& MapSize, const Vector2& CubeSize, const std::vector<BoundingBox>& EnvironmentBoundingBoxes) : m_Camera {Camera3D {{MapSize.y / 2, CubeSize.x + PlayerProperties::PLAYER_SIZE / 2, MapSize.x / 2}, Vector3Add(Camera().position, GetCameraForward(&Camera())), VectorConstants::UP_VECTOR, PlayerProperties::PLAYER_FOV, CAMERA_PERSPECTIVE}}, m_GrapplingHookGun {{}}, m_CurrentPlayerState {PlayerProperties::PlayerStates::Default}, m_EnvironmentBoundingBoxes {EnvironmentBoundingBoxes}
{
}

void Player::Update()
{
	switch (m_CurrentPlayerState)
	{
		case PlayerProperties::PlayerStates::Default:
			RequestMovement();
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

void Player::AttachGun(const GrapplingHookGun& Gun)
{
	m_GrapplingHookGun = Gun;
}

bool Player::IsColliding()
{
	BoundingBox playerBoundingBox {GenerateBoundingBox()};

	for (const BoundingBox& boundingBox : m_EnvironmentBoundingBoxes)
	{
		if (CheckCollisionBoxes(GenerateBoundingBox(), boundingBox))
		{
			return true;
		}
	}

	return false;
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

BoundingBox Player::GenerateBoundingBox()
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
	DrawBoundingBox(GenerateBoundingBox(), DebugProperties::DEBUG_COLOUR);

	DrawSphere(Camera().target, DebugProperties::SPHERE_RADIUS, DebugProperties::DEBUG_COLOUR);
}

void Player::RequestShot()
{
	if (IsKeyDown(KEY_E))
	{
		m_CurrentPlayerState = PlayerProperties::PlayerStates::Grapple;
	}
}

void Player::RequestMovement()
{
	Camera3D& player {Camera()};

	const Vector3 oldPlayerPosition {player.position};
	const Vector3 oldTargetPosition {player.target};

	UpdateCameraPro(&Camera(), Movement(), Rotation(), 0.f); 

	if (IsColliding())
	{
		player.position = oldPlayerPosition;
		player.target = oldTargetPosition;
	}
}

void Player::Shoot()
{
	if (IsColliding())
	{
		m_CurrentPlayerState = PlayerProperties::PlayerStates::Falling;
	}
	else
	{
		Camera3D& player {Camera()};
	
		const Vector3 relativeTargetPosition {Vector3Subtract(m_Camera.target, m_Camera.position)};
	
		player.position = m_GrapplingHookGun.Shoot(m_Camera.position, Vector3Normalize(relativeTargetPosition), m_CurrentPlayerState);
	
		player.target = Vector3Add(player.position, relativeTargetPosition);
	}
}
