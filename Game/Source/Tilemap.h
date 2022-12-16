#pragma once
#include "DataTypes.h"

class fw::Mesh;
class fw::Texture;
class fw::SpriteSheet;
struct fw::SpriteInfo;
class fw::Camera;
class fw::ShaderProgram;
class Pathfinder;

enum class TileType : unsigned char
{
    Sand,
    Water,
    Wall,
    NumTypes
};

struct TileProperties
{
    SpriteInfo* m_pSpriteInfo = nullptr;
    bool m_Walkable = true;
};

class Tilemap
{
public:
    Tilemap(Mesh* pMesh, ShaderProgram* pShaderProgram, Texture* pTexture, SpriteSheet* pSpriteSheet, TileType* pLayout, iVec2 Size);
    ~Tilemap();

    TileProperties GetTilePropertiesAtWorldPosition(Vec2 worldPosition);
    TileProperties GetTilePropertiesAtTilePosition(iVec2 tilePosition);
    iVec2 GetTilePositionFromWorldPosition(Vec2 worldPosition);
    Vec2 GetWorldPositionFromTilePosition(iVec2 tilePosition);
    iVec2 GetTilePositionFromIndex(int index);
    int GetIndexFromTilePosition(iVec2 tilePosition);

    Vec2 GetTileSize() { return m_TileSize; }
    int GetMapWidth() { return m_MapSize.x; }
    int GetMapHeight() { return m_MapSize.y; }
    Pathfinder* GetPathfinder() { return m_pPathfinder; }

    TileType GetTileTypeAtIndex(int index);
    void SetTileTypeAtIndex(int index, TileType type);

    void Draw(Camera* pCamera);

    void RebuildMesh();

protected:

    Vec2 m_Position = { 0, 0 };
    Vec2 m_TileDrawPosition = { 0, 0 };
    Vec2 m_Scale = { 2, 2 };
    float m_Angle = 0.0f;

    Vec2 m_TileSize = m_Scale;

    TileProperties* m_pTileProperties = nullptr;
    SpriteSheet* m_pSpriteSheet = nullptr;
    Texture* m_pTexture = nullptr;
    Mesh* m_pMesh = nullptr;
    ShaderProgram* m_pShaderProgram = nullptr;

    TileType* m_pLayout = nullptr;
    iVec2 m_MapSize = { 0, 0 };

    Pathfinder* m_pPathfinder = nullptr;

};
