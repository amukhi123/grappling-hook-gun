#pragma once

#include "IBase.h"

namespace DebugProperties
{
	inline constexpr Color DEBUG_COLOUR {RED};

	inline constexpr int DEBUG_KEY {KEY_F};

	// Sphere
	inline constexpr float SPHERE_RADIUS {0.01f};

	// Capsule
	inline constexpr float CAPSULE_RADIUS {0.05f};
	inline constexpr int CAPSUPLE_SLICES {5};
	inline constexpr int CAPSULE_RINGS {5};
};

class Debug
{
protected:
	Debug();

	virtual void DebugActions() = 0;

	void CheckDebugActions();
private:
	bool m_IsDebugModeEnabled {};

	void FlipDebugMode();
};
