#include "Debug.h"

Debug::Debug() : m_IsDebugModeEnabled {false}
{
}

void Debug::CheckDebugActions()
{
	if (IsKeyPressed(DebugProperties::DEBUG_KEY))
	{
		FlipDebugMode();
	}

	if (m_IsDebugModeEnabled)
	{
		DebugActions();
	}
}

void Debug::FlipDebugMode()
{
	m_IsDebugModeEnabled = !m_IsDebugModeEnabled;
}
