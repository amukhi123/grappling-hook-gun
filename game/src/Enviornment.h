#pragma once

#include <vector>

#include "IGameBase.h"
#include "Debug.h"

namespace EnvironmentProperties
{
	// This does not include the ground or the roof
	inline constexpr int MAP_HEIGHT {6};
}

class Environment : public IGameBase, public Debug
{
public:
	Environment();

	~Environment();

	void Update() override;

	Vector2 CubeSize() const;

	Vector2 PlayerSpawnPosition() const;

	std::vector<BoundingBox> BoundingBoxes() const;
private:
	Model m_WallCubeModel {};
	Model m_GroundCubeModel {};

	Texture m_WallCubeTexture {};
	Texture m_GroundCubeTexture {};

	Image m_MapImage {};

	Vector2 m_CubeSize {};
	Vector2 m_PlayerSpawnPosition {};

	bool m_IsFinishedGeneratingBoundingBoxes {};

	std::vector<BoundingBox> m_BoundingBoxes {};

	void GenerateMap();

	bool CompareColour(const Color& LeftColour, const Color& RightColour) const;

	void AddBoundingBox(const Vector3& MinBoundingBoxPosition, const Vector3& MaxBoundingBoxPosition);

	void DebugActions() override;
};
