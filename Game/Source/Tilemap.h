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

    void Draw(Camera* pCamera);

protected:

    Vec2 m_Position = { -4.5f, -4.5f };
    Vec2 tempPosition = { 0, 0 };
    Vec2 m_Scale = { 1, 1};
    float m_Angle = 0.0f;

    int m_Width = 5;
    int m_Height = 10;

    TileProperties* m_pTileProperties = nullptr;
    SpriteSheet* m_pSpriteSheet = nullptr;
    Texture* m_pTexture = nullptr;
    Mesh* m_pMesh = nullptr;
    ShaderProgram* m_pShaderProgram = nullptr;

    unsigned char* m_pLayout = nullptr;

};
