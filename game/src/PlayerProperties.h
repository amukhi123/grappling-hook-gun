#pragma once

namespace PlayerProperties
{
	// The average running speed fpr a human male is 13 km/h or 3.61111 m/s
	inline constexpr float PLAYER_MOVEMENT_SPEED {3.61111f};
	// The peak turning speed of a human head is 240 degrees/s
	inline constexpr float PLAYER_ROTATION_SPEED {240.f};
	inline constexpr float PLAYER_FOV {45.f};
	inline constexpr float PLAYER_SIZE {2.f};
}
