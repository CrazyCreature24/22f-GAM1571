#pragma once
#include "DataTypes.h"

class fw::Mesh;
class fw::Texture;
class fw::SpriteSheet;
struct fw::SpriteInfo;

enum class TileType
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
    Tilemap(Mesh* pMesh, Texture* pTexture, SpriteSheet* pSpriteSheet);
    ~Tilemap();

protected:

    int m_Width = 0;
    int m_Height = 0;

    TileProperties* m_pTileProperties = nullptr;
    SpriteSheet* m_pSpriteSheet = nullptr;
    Texture* m_pTexture = nullptr;
    Mesh* m_pMesh = nullptr;

};
