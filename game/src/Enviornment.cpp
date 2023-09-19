#include "Enviornment.h"

Environment::Environment() : m_WallCubeModel {LoadModel("resources/Cube.obj")}, m_GroundCubeModel {LoadModel("resources/Cube.obj")}, m_WallCubeTexture {LoadTexture("resources/WallCubeTexture.png")}, m_GroundCubeTexture {LoadTexture("resources/GroundCubeTexture.png")}, m_MapImage {LoadImage("resources/Map.png")}, m_MapSize {static_cast<float>(m_MapImage.width), static_cast<float>(m_MapImage.height)}, m_CubeSize {2.f, 2.f} 
{
	m_WallCubeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_WallCubeTexture; 
	m_GroundCubeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_GroundCubeTexture; 
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
	CreateMap();
}

void Environment::CreateMap()
{
	constexpr Color GROUND_COLOUR {BLACK};
	constexpr Color WALL_COLOUR {WHITE};

	const Vector2 mapSize {MapSize()};
	const Vector2 cubeSize {CubeSize()};


	for (int x {0}; x < mapSize.x; ++x)
	{
		for (int y {0}; y < mapSize.y; ++y)
		{
			const Color cellColour {GetImageColor(m_MapImage, x, y)};
		
			if (CompareColour(cellColour, GROUND_COLOUR) || CompareColour(cellColour, WALL_COLOUR))
			{
				const float placementLength {x * cubeSize.x};
				const float placementWidth {y * cubeSize.x};

				DrawModel(m_GroundCubeModel, {placementLength, 0.f, placementWidth}, 1.f, WHITE);		

				const float roofPlacementHeight {cubeSize.y * 3};

				DrawModel(m_WallCubeModel, {placementLength, roofPlacementHeight, placementWidth}, 1.f, WHITE);		

				if (CompareColour(cellColour, WALL_COLOUR))
				{
					DrawModel(m_WallCubeModel, {placementLength, roofPlacementHeight - cubeSize.y, placementWidth}, 1.f, WHITE);

					const float groundPlacementHeight {roofPlacementHeight - cubeSize.y * 2};

					DrawModel(m_WallCubeModel, {placementLength, groundPlacementHeight, placementWidth}, 1.f, WHITE);
				}
			}
		}
	}
}

bool Environment::CompareColour(const Color& LeftColour, const Color& RightColour) const
{
	return LeftColour.r == RightColour.r && LeftColour.b == RightColour.b && LeftColour.g == RightColour.g && LeftColour.a == RightColour.a;
}

Vector2 Environment::MapSize() const
{
	return m_MapSize;
}

Vector2 Environment::CubeSize() const
{
	return m_CubeSize;
}
