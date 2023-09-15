#pragma once

#include "raylib.h"

namespace VectorConstants
{
	inline constexpr Vector3 ONE_VECTOR {1.f, 1.f, 1.f};
	inline constexpr Vector3 ZERO_VECTOR {0.f, 0.f, 0.f};
	inline constexpr Vector3 UP_VECTOR {0.f, 1.f, 0.f}; 
};

class IGameBase
{
public:
	virtual void Update() = 0;
};
