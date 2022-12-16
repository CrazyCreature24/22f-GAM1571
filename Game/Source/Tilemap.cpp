#include "Framework.h"
#include "AI/Pathfinder.h"
#include "Tilemap.h"



Tilemap::Tilemap(Mesh* pMesh, ShaderProgram* pShaderProgram, Texture* pTexture, SpriteSheet* pSpriteSheet, TileType* pLayout, iVec2 Size)
{
    m_pMesh = pMesh;
    m_pTexture = pTexture;
    m_pSpriteSheet = pSpriteSheet;
    m_pShaderProgram = pShaderProgram;


    m_pTileProperties = new TileProperties[(int)TileType::NumTypes]{
        {m_pSpriteSheet->GetSpriteInfo("TileSand"), true},
        {m_pSpriteSheet->GetSpriteInfo("TileWater5"), false},
        {m_pSpriteSheet->GetSpriteInfo("TileMountain1"), false}
    };

    //This brings in the Tilemap layout from Game and dynamically creates an array to copy the map oveer into.
    //I have not tried to flip the array yet. I will try it over the break.
    m_MapSize = Size;
    int NumTiles = m_MapSize.x * m_MapSize.y;
    m_pLayout = new TileType[NumTiles];

    for (int i = 0; i < NumTiles; i++)
    {
        m_pLayout[i] = pLayout[i];
    }

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
    
    int tileIndex = m_MapSize.x * TilePosition.y + TilePosition.x;

    return m_pTileProperties[(int)m_pLayout[tileIndex]];
}

TileProperties Tilemap::GetTilePropertiesAtTilePosition(iVec2 tilePosition)
{
    int tileIndex = m_MapSize.x * tilePosition.y + tilePosition.x;

    return m_pTileProperties[(int)m_pLayout[tileIndex]];
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
    return iVec2(index % m_MapSize.x, index / m_MapSize.x);
}

int Tilemap::GetIndexFromTilePosition(iVec2 tilePosition)
{
    return tilePosition.y * m_MapSize.x + tilePosition.x;
}

TileType Tilemap::GetTileTypeAtIndex(int index)
{
    return m_pLayout[index];
}

void Tilemap::SetTileTypeAtIndex(int index, TileType type)
{
    m_pLayout[index] = type;
}

void Tilemap::Draw(Camera* pCamera)
{
    m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, 0, m_pTexture, pCamera, Vec2(1,1), Vec2(0,0));
}

void Tilemap::RebuildMesh()
{
    m_pMesh->ClearVerts();

    std::vector<VertexFormat> boxVerts;
    for (int j = 0; j < m_MapSize.y; j++)
    {
        for (int i = 0; i < m_MapSize.x; i++)
        {
            SpriteInfo* spriteInfo = m_pTileProperties[(int)m_pLayout[j * m_MapSize.x + i]].m_pSpriteInfo;
            Vec2 uvScale = spriteInfo->UVScale;
            Vec2 uvOffset = spriteInfo->UVOffset;

            Vec2 Offset = Vec2((float)i, (float)j) * m_TileSize / m_Scale;

            boxVerts.push_back(VertexFormat(Vec2(-0.5f, -0.5f) + Offset, 100, 255, 255, 255, 0 * uvScale.x + uvOffset.x, 0 * uvScale.y + uvOffset.y));
            boxVerts.push_back(VertexFormat(Vec2(-0.5f, 0.5f) + Offset, 255, 255, 255, 255, 0 * uvScale.x + uvOffset.x, 1 * uvScale.y + uvOffset.y));
            boxVerts.push_back(VertexFormat(Vec2(0.5f, 0.5f) + Offset, 255, 255, 255, 255, 1 * uvScale.x + uvOffset.x, 1 * uvScale.y + uvOffset.y));
            boxVerts.push_back(VertexFormat(Vec2(0.5f, 0.5f) + Offset, 255, 255, 255, 255, 1 * uvScale.x + uvOffset.x, 1 * uvScale.y + uvOffset.y));
            boxVerts.push_back(VertexFormat(Vec2(-0.5f, -0.5f) + Offset, 255, 255, 255, 255, 0 * uvScale.x + uvOffset.x, 0 * uvScale.y + uvOffset.y));
            boxVerts.push_back(VertexFormat(Vec2(0.5f, -0.5f) + Offset, 100, 255, 255, 255, 1 * uvScale.x + uvOffset.x, 0 * uvScale.y + uvOffset.y));
        }
    }

    m_pMesh->AddVerts(boxVerts);

    m_pMesh->RebuildVBO();
}

