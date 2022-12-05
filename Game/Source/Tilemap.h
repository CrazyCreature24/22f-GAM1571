#pragma once
#include "DataTypes.h"

class fw::Mesh;
class fw::Texture;
class fw::SpriteSheet;
struct fw::SpriteInfo;
class fw::Camera;
class fw::ShaderProgram;

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
    Tilemap(Mesh* pMesh, ShaderProgram* pShaderProgram, Texture* pTexture, SpriteSheet* pSpriteSheet);
    ~Tilemap();

    TileProperties GetTilePropertiesAtWorldPosition(Vec2 worldPosition);
    TileProperties GetTilePropertiesAtTilePosition(iVec2 tilePosition);
    iVec2 GetTilePositionFromWorldPosition(Vec2 worldPosition);
    Vec2 GetWorldPositionFromTilePosition(iVec2 tilePosition);

    void Draw(Camera* pCamera);

protected:

    Vec2 m_Position = { -1, -1 };
    Vec2 m_TileDrawPosition = { 0, 0 };
    Vec2 m_Scale = { 1, 1};
    float m_Angle = 0.0f;

    Vec2 m_TileSize = m_Scale;
    int m_Width = 5;
    int m_Height = 10;

    TileProperties* m_pTileProperties = nullptr;
    SpriteSheet* m_pSpriteSheet = nullptr;
    Texture* m_pTexture = nullptr;
    Mesh* m_pMesh = nullptr;
    ShaderProgram* m_pShaderProgram = nullptr;

    unsigned char* m_pLayout = nullptr;

};
