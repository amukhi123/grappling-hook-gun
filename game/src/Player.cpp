#include <vector>

#include "Player.h"
#include "rcamera.h"

Player::Player(const Vector2& PlayerSpawnPosition, const Vector2& CubeSize, const std::vector<BoundingBox>& EnvironmentBoundingBoxes) : m_Camera {Camera3D {{PlayerSpawnPosition.x, PlayerProperties::MINIMUM_Y_POSITION, PlayerSpawnPosition.y}, Vector3Add(Camera().position, GetCameraForward(&Camera())), VectorConstants::UP_VECTOR, PlayerProperties::PLAYER_FOV, CAMERA_PERSPECTIVE}}, m_GrapplingHookGun {{}}, m_CurrentPlayerState {PlayerProperties::PlayerStates::Default}, m_EnvironmentBoundingBoxes {EnvironmentBoundingBoxes}
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
			Fall();
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

void Player::DebugActions()
{
	DrawBoundingBox(GenerateBoundingBox(), DebugProperties::DEBUG_COLOUR);

	DrawSphere(Camera().target, DebugProperties::SPHERE_RADIUS, DebugProperties::DEBUG_COLOUR);
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

	const float speedMultiplier {PlayerProperties::PLAYER_ROTATION_SPEED * GetFrameTime()};

	if (IsKeyDown(KEY_UP))
	{
		rotationVector.y -= speedMultiplier;
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		rotationVector.y += speedMultiplier;
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		rotationVector.x += speedMultiplier;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		rotationVector.x -= speedMultiplier;
	}

	return rotationVector;
}

BoundingBox Player::GenerateBoundingBox()
{
	const float halfPlayerSize {PlayerProperties::PLAYER_SIZE / 2};

	const Vector3 bottomLeftPlayerPosition {Vector3Subtract(Camera().position, VectorHelpers::Vector3FromFloat(halfPlayerSize))};

	const BoundingBox playerBoundingBox {bottomLeftPlayerPosition, Vector3Add(bottomLeftPlayerPosition, VectorHelpers::Vector3FromFloat(PlayerProperties::PLAYER_SIZE))};

	return playerBoundingBox;
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

		const Vector3 oldPlayerPosition {player.position};

		player.position = m_GrapplingHookGun.Shoot(m_Camera.position, Vector3Normalize(relativeTargetPosition), m_CurrentPlayerState);

		if (IsColliding())
		{
			player.position = oldPlayerPosition;

			m_CurrentPlayerState = PlayerProperties::PlayerStates::Falling;
		}

		if (player.position.y < PlayerProperties::MINIMUM_Y_POSITION)
		{
			player.position.y = PlayerProperties::MINIMUM_Y_POSITION;

			m_CurrentPlayerState = PlayerProperties::PlayerStates::Default;
		}

		player.target = Vector3Add(player.position, relativeTargetPosition);
	}
}

void Player::Fall()
{
	Camera3D& player {Camera()};

	const float oldTargetYPos {player.target.y};

	const float gravity {GetFrameTime() * PlayerProperties::PLAYER_FALL_SPEED};

	player.position.y -= gravity;
	player.target.y -= gravity;

	if (Camera().position.y < PlayerProperties::MINIMUM_Y_POSITION)
	{
		m_CurrentPlayerState = PlayerProperties::PlayerStates::Default;

		player.position.y = PlayerProperties::MINIMUM_Y_POSITION;

		player.target.y = oldTargetYPos;
	}
}
