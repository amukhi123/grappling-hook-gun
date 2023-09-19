#include "IUserInterfaceBase.h"

IUserInterfaceBase::IUserInterfaceBase(const char* TexutrePath) : m_UserInterfaceTexture {LoadTexture(TexutrePath)}
{
}

Texture IUserInterfaceBase::UserInterfaceTexture() const
{
	return m_UserInterfaceTexture;
}
