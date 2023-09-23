#pragma once

#include "IBase.h"
#include "raymath.h"

namespace VectorConstants
{
	inline constexpr Vector3 UP_VECTOR {0.f, 1.f, 0.f}; 
};

namespace VectorHelpers
{
	inline Vector3 Vector3FromFloat(const float& ComponentValues)
	{
		return {ComponentValues, ComponentValues, ComponentValues};
	}
};

class IGameBase : public IBase
{
};
