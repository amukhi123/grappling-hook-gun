#include "Enviornment.h"

Environment::Environment() : m_MapImage {LoadImage("resources/Map.png")}, m_MapTexure {LoadTextureFromImage(m_MapImage)}, m_CubeTexture {LoadTexture("resources/CubeTextures.png")}, m_MapMesh {GenMeshCubicmap(m_MapImage, VectorConstants::ONE_VECTOR)}, m_MapModel {LoadModelFromMesh(m_MapMesh)}, m_MapPosition {0, 0, 0} 
{
	m_MapModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_CubeTexture;
}

Environment::~Environment()
{
	UnloadImage(m_MapImage);
	UnloadTexture(m_MapTexure);
	UnloadTexture(m_CubeTexture);
	UnloadMesh(m_MapMesh);
	UnloadModel(m_MapModel);
}

void Environment::Update()
{
	DrawModel(m_MapModel, m_MapPosition, 1, WHITE);
}
