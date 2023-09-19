#pragma once

#include "IBase.h"

class IUserInterfaceBase : public IBase
{
public:
	IUserInterfaceBase(const char* TexutrePath);

	Texture UserInterfaceTexture() const;

private:
	Texture m_UserInterfaceTexture {};
};
