#include "Enviornment.h"
#include "PlayerProperties.h"

Environment::Environment() : m_WallCubeModel {LoadModel("resources/Cube.obj")}, m_GroundCubeModel {LoadModel("resources/Cube.obj")}, m_WallCubeTexture {LoadTexture("resources/WallCubeTexture.png")}, m_GroundCubeTexture {LoadTexture("resources/GroundCubeTexture.png")}, m_MapImage {LoadImage("resources/Map.png")}, m_CubeSize {2.f, 2.f}, m_BoundingBoxes {}, m_IsFinishedGeneratingBoundingBoxes {false}, m_PlayerSpawnPosition {}
{
	m_WallCubeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_WallCubeTexture; 
	m_GroundCubeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_GroundCubeTexture; 

	// Called to generate bounding boxes
	GenerateMap();
}

Environment::~Environment()
{
	UnloadModel(m_GroundCubeModel);
	UnloadModel(m_WallCubeModel);
	UnloadTexture(m_GroundCubeTexture);
	UnloadTexture(m_WallCubeTexture);
	UnloadImage(m_MapImage);
}

void Environment::Update()
{
	GenerateMap();
	CheckDebugActions();
}

Vector2 Environment::CubeSize() const
{
	return m_CubeSize;
}

Vector2 Environment::PlayerSpawnPosition() const
{
	return m_PlayerSpawnPosition;
}

std::vector<BoundingBox> Environment::BoundingBoxes() const
{
	return m_BoundingBoxes;
}

void Environment::GenerateMap()
{
	constexpr Color GROUND_COLOUR {BLACK};
	constexpr Color WALL_COLOUR {WHITE};
	constexpr Color PLAYER_SPAWN_COLOUR {0.f, 0.f, 255.f, 255.f};

	const Vector2 mapSize {m_MapImage.width, m_MapImage.height};
	const Vector2 cubeSize {CubeSize()};

	for (int x {0}; x < mapSize.x; ++x)
	{
		for (int y {0}; y < mapSize.y; ++y)
		{
			const Color cellColour {GetImageColor(m_MapImage, x, y)};
		
			if (CompareColour(cellColour, GROUND_COLOUR) || CompareColour(cellColour, WALL_COLOUR) || CompareColour(cellColour, PLAYER_SPAWN_COLOUR))
			{
				const float placementLength {x * cubeSize.x};
				const float placementWidth {y * cubeSize.x};

				const Vector3 groundCubePosition {placementLength, 0.f, placementWidth};

				DrawModel(m_GroundCubeModel, groundCubePosition, 1.f, WHITE);

				const Vector3 cubeTopRightPosition {cubeSize.x, cubeSize.y, cubeSize.x};
				const Vector3 halfCubeSize {cubeSize.x / 2, cubeSize.y / 2, cubeSize.x / 2};
				const Vector3 groundCubeBottomLeftPosition {Vector3Subtract(groundCubePosition, halfCubeSize)};

				AddBoundingBox(groundCubeBottomLeftPosition, Vector3Add(groundCubeBottomLeftPosition, cubeTopRightPosition));

				const float roofPlacementHeight {cubeSize.y * (EnvironmentProperties::MAP_HEIGHT + 1)};

				const Vector3 roofCubePosition {placementLength, roofPlacementHeight, placementWidth};

				DrawModel(m_WallCubeModel, roofCubePosition, 1.f, WHITE);		
				const Vector3 roofBottomLeftPosition {Vector3Subtract(roofCubePosition, halfCubeSize)};

				AddBoundingBox(roofBottomLeftPosition, Vector3Add(roofBottomLeftPosition, cubeTopRightPosition));

				if (CompareColour(cellColour, PLAYER_SPAWN_COLOUR))
				{
					m_PlayerSpawnPosition = {placementLength, placementWidth};
				}

				if (CompareColour(cellColour, WALL_COLOUR))
				{
					for (int y {0}; y < EnvironmentProperties::MAP_HEIGHT; ++y)
					{
						const float wallCubeHeightPosition {roofPlacementHeight - cubeSize.y * (y + 1)};

						const Vector3 wallCubePosition {placementLength, wallCubeHeightPosition, placementWidth};

						DrawModel(m_WallCubeModel, wallCubePosition, 1.f, WHITE);

						const Vector3 wallCubeBottomLeftPosition {Vector3Subtract(wallCubePosition, halfCubeSize)};

						AddBoundingBox(wallCubeBottomLeftPosition, Vector3Add(wallCubeBottomLeftPosition, cubeTopRightPosition));
					}
				}
			}
		}
	}

	if (!m_IsFinishedGeneratingBoundingBoxes)
	{
		m_IsFinishedGeneratingBoundingBoxes = true;
	}
}

bool Environment::CompareColour(const Color& LeftColour, const Color& RightColour) const
{
	return LeftColour.r == RightColour.r && LeftColour.b == RightColour.b && LeftColour.g == RightColour.g && LeftColour.a == RightColour.a;
}

void Environment::AddBoundingBox(const Vector3& MinBoundingBoxPosition, const Vector3& MaxBoundingBoxPosition)
{
	if (!m_IsFinishedGeneratingBoundingBoxes)
	{
		m_BoundingBoxes.push_back({MinBoundingBoxPosition, MaxBoundingBoxPosition});
	}
}

void Environment::DebugActions()
{
	for (const BoundingBox& boundingBox : m_BoundingBoxes) 
	{
		DrawBoundingBox(boundingBox, DebugProperties::DEBUG_COLOUR);
	}
}
