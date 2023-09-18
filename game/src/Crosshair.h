#pragma once

#include "IUserInterfaceBase.h"

class Crosshair : public IUserInterfaceBase
{
public:
	Crosshair();

	void Update() override;
};
