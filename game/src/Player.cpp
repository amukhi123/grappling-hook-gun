#include "Player.h"

Player::Player() : m_PlayerPosition {1.f, 0.5f, 1.f}, m_Camera {Camera3D{m_PlayerPosition, {5,0,5}, VectorConstants::UP_VECTOR, PlayerProperties::PLAYER_FOV, CAMERA_PERSPECTIVE}}
{
}

void Player::Update()
{
	UpdateCamera(&Camera(), CAMERA_FIRST_PERSON); 
}

Camera3D& Player::Camera() 
{
	return m_Camera;
}
