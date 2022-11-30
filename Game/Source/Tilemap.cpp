#include "Framework.h"
#include "Tilemap.h"


Tilemap::Tilemap(Mesh* pMesh, Texture* pTexture, SpriteSheet* pSpriteSheet)
{
    m_pTileProperties = new TileProperties[static_cast<int>(TileType::NumTypes)];

}

Tilemap::~Tilemap()
{
    delete m_pTileProperties;
}

