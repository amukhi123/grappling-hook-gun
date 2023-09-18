#pragma once

#include "IBase.h"
#include "raymath.h"

namespace VectorConstants
{
	// Remove and use built in UP function
	inline constexpr Vector3 UP_VECTOR {0.f, 1.f, 0.f}; 
};

class IGameBase : public IBase
{
};
