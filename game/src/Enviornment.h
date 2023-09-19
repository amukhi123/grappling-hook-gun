#pragma once

#include "IGameBase.h"

class Environment : public IGameBase
{
public:
	Environment();

	~Environment();

	void Update() override;

	Vector2 MapSize() const;

	Vector2 CubeSize() const;

private:
	Model m_WallCubeModel {};
	Model m_GroundCubeModel {};

	Texture m_WallCubeTexture {};
	Texture m_GroundCubeTexture {};

	Image m_MapImage {};

	Vector2 m_MapSize {};
	Vector2 m_CubeSize {};

	void CreateMap();

	bool CompareColour(const Color& LeftColour, const Color& RightColour) const;
};
