#pragma once

#include "raylib.h"
#include "raymath.h"

namespace VectorConstants
{
	inline constexpr Vector3 UP_VECTOR {0.f, 1.f, 0.f}; 
};

class IGameBase
{
public:
	virtual void Update() = 0;
};
