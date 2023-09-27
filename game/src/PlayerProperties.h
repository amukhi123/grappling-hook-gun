#pragma once

namespace PlayerProperties
{
	// The average running speed for a human male is 13 km/h or 3.61111 m/s
	inline constexpr float PLAYER_MOVEMENT_SPEED {3.61111f};
	// The average sprinting speed for  a human male is 19.52 mph or 8.7262208 m/s
	inline constexpr float PLAYER_SPRINT_SPEED {8.7262208f};
	// The peak turning speed of a human head is 240 degrees/s, we take a little bit less to estimate the average turning speed
	inline constexpr float PLAYER_ROTATION_SPEED {140.f};
	inline constexpr float PLAYER_FALL_SPEED {10.f};
	inline constexpr float PLAYER_FOV {45.f};
	inline constexpr float PLAYER_SIZE {2.f};
	inline constexpr float MINIMUM_Y_POSITION {3.f};

	enum class PlayerStates
	{
		// Currently default encompesses idle, walk and sprint
		Default,
		Grapple,
		InAir,
		Falling
	};
}
