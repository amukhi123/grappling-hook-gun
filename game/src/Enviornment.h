#pragma once

#include "IGameBase.h"

class Environment : public IGameBase
{
public:
	Environment();

	~Environment();

	void Update() override;

private:
	Image m_MapImage {};

	Texture m_MapTexure {};
	Texture m_CubeTexture {};

	Mesh m_MapMesh {};

	Model m_MapModel {};

	Vector3 m_MapPosition {};
};
