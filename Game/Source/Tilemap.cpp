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

    m_pPathfinder = new Pathfinder(this);

    RebuildMesh();
}

Tilemap::~Tilemap()
{
    delete m_pTileProperties;

    delete m_pLayout;

    delete m_pPathfinder;
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

iVec2 Tilemap::GetTilePositionFromIndex(int index)
{
    return iVec2(index % m_Width, index / m_Width);
}

void Tilemap::Draw(Camera* pCamera)
{
    m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, 0, m_pTexture, pCamera, Vec2(1,1), Vec2(0,0));
}

void Tilemap::RebuildMesh()
{
    m_pMesh->ClearVerts();

    std::vector<VertexFormat> boxVerts;
    for (int j = 0; j < m_Height; j++)
    {
        for (int i = 0; i < m_Width; i++)
        {
            SpriteInfo* spriteInfo = m_pTileProperties[m_pLayout[j * m_Width + i]].m_pSpriteInfo;
            Vec2 uvScale = spriteInfo->UVScale;
            Vec2 uvOffset = spriteInfo->UVOffset;

            boxVerts.push_back(VertexFormat(-0.5f + (m_TileSize.x * i), -0.5f + (m_TileSize.y * j), 100, 255, 255, 255, 0 * uvScale.x + uvOffset.x, 0 * uvScale.y + uvOffset.y));
            boxVerts.push_back(VertexFormat(-0.5f + (m_TileSize.x * i), 0.5f + (m_TileSize.y * j), 255, 255, 255, 255, 0 * uvScale.x + uvOffset.x, 1 * uvScale.y + uvOffset.y));
            boxVerts.push_back(VertexFormat(0.5f + (m_TileSize.x * i), 0.5f + (m_TileSize.y * j), 255, 255, 255, 255, 1 * uvScale.x + uvOffset.x, 1 * uvScale.y + uvOffset.y));
            boxVerts.push_back(VertexFormat(0.5f + (m_TileSize.x * i), 0.5f + (m_TileSize.y * j), 255, 255, 255, 255, 1 * uvScale.x + uvOffset.x, 1 * uvScale.y + uvOffset.y));
            boxVerts.push_back(VertexFormat(-0.5f + (m_TileSize.x * i), -0.5f + (m_TileSize.y * j), 255, 255, 255, 255, 0 * uvScale.x + uvOffset.x, 0 * uvScale.y + uvOffset.y));
            boxVerts.push_back(VertexFormat(0.5f + (m_TileSize.x * i), -0.5f + (m_TileSize.y * j), 100, 255, 255, 255, 1 * uvScale.x + uvOffset.x, 0 * uvScale.y + uvOffset.y));
        }
    }

    m_pMesh->AddVerts(boxVerts);

    m_pMesh->RebuildVBO();
}

