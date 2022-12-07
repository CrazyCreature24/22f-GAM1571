#include "Framework.h"
#include "AI/Pathfinder.h"
#include "Tilemap.h"



Tilemap::Tilemap(Mesh* pMesh, ShaderProgram* pShaderProgram, Texture* pTexture, SpriteSheet* pSpriteSheet)
{
    m_pMesh = pMesh;
    m_pTexture = pTexture;
    m_pSpriteSheet = pSpriteSheet;
    m_pShaderProgram = pShaderProgram;


    m_pTileProperties = new TileProperties[static_cast<int>(TileType::NumTypes)]{
        {m_pSpriteSheet->GetSpriteInfo("TileSand"), true},
        {m_pSpriteSheet->GetSpriteInfo("TileWater5"), false},
        {m_pSpriteSheet->GetSpriteInfo("TileMountain1"), false}
    };

    /*m_pLayout = new unsigned char[m_Width * m_Height]{
        1, 2, 2, 2, 2,
        1, 0, 0, 0, 2,
        1, 0, 0, 0, 2,
        1, 0, 0, 0, 2,
        1, 0, 0, 0, 2,
        1, 0, 0, 0, 2,
        1, 0, 0, 0, 2,
        1, 0, 0, 0, 2,
        1, 0, 0, 0, 2,
        1, 2, 2, 2, 2
    };*/

    m_pLayout = new unsigned char[m_Width * m_Height]{
        static_cast<unsigned char>(TileType::Water), static_cast<unsigned char>(TileType::Wall), static_cast<unsigned char>(TileType::Wall), static_cast<unsigned char>(TileType::Wall), static_cast<unsigned char>(TileType::Wall),
        static_cast<unsigned char>(TileType::Water), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Wall),
        static_cast<unsigned char>(TileType::Water), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Wall),
        static_cast<unsigned char>(TileType::Water), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Wall),
        static_cast<unsigned char>(TileType::Water), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Wall),
        static_cast<unsigned char>(TileType::Water), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Wall),
        static_cast<unsigned char>(TileType::Water), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Wall),
        static_cast<unsigned char>(TileType::Water), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Wall),
        static_cast<unsigned char>(TileType::Water), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Sand), static_cast<unsigned char>(TileType::Wall),
        static_cast<unsigned char>(TileType::Water), static_cast<unsigned char>(TileType::Wall), static_cast<unsigned char>(TileType::Wall), static_cast<unsigned char>(TileType::Wall), static_cast<unsigned char>(TileType::Wall)
    };

}

Tilemap::~Tilemap()
{
    delete m_pTileProperties;

    delete m_pLayout;
}

TileProperties Tilemap::GetTilePropertiesAtWorldPosition(Vec2 worldPosition)
{
    iVec2 TilePosition = iVec2((int)(worldPosition.x / m_TileSize.x), (int)(worldPosition.y / m_TileSize.y));
    
    int tileIndex = m_Width * TilePosition.y + TilePosition.x;

    return m_pTileProperties[m_pLayout[tileIndex]];
}

TileProperties Tilemap::GetTilePropertiesAtTilePosition(iVec2 tilePosition)
{
    int tileIndex = m_Width * tilePosition.y + tilePosition.x;

    return m_pTileProperties[m_pLayout[tileIndex]];
}

iVec2 Tilemap::GetTilePositionFromWorldPosition(Vec2 worldPosition)
{
    return iVec2((int)(worldPosition.x / m_TileSize.x), (int)(worldPosition.y / m_TileSize.y));
}

Vec2 Tilemap::GetWorldPositionFromTilePosition(iVec2 tilePosition)
{
    return Vec2(m_Position.x + (tilePosition.x * m_TileSize.x), m_Position.y + (tilePosition.y * m_TileSize.y));
}

void Tilemap::Draw(Camera* pCamera)
{
    float baseX = m_Position.x;
    m_TileDrawPosition = m_Position;

    for (int i = 0; i < m_Width * m_Height; i++)
    {
        SpriteInfo* spriteInfo = m_pTileProperties[m_pLayout[i]].m_pSpriteInfo;

        m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_TileDrawPosition, 0, m_pTexture, pCamera, m_pSpriteSheet->GetUVScale(spriteInfo->Name), m_pSpriteSheet->GetUVOffset(spriteInfo->Name));

        if ((i + 1) % m_Width == 0)
        {
            m_TileDrawPosition.x = baseX;
            m_TileDrawPosition.y += m_TileSize.y;
        }
        else
        {
            m_TileDrawPosition.x += m_TileSize.x;
        }
    }
}

