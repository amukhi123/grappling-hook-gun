#pragma once

#include "IBase.h"

class IUserInterfaceBase : public IBase
{
public:
	inline IUserInterfaceBase(const char* TexutrePath) : m_UserInterfaceTexture {LoadTexture(TexutrePath)}
	{
	}

	inline Texture UserInterfaceTexture() const
	{
		return m_UserInterfaceTexture;
	}

private:
	Texture m_UserInterfaceTexture {};
};
