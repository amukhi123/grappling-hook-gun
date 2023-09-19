#pragma once

#include "IBase.h"

namespace DebugProperties
{
	inline constexpr Color DEBUG_COLOUR {RED};

	inline constexpr int DEBUG_KEY {KEY_F};
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
