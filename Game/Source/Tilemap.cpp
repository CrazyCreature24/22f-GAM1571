#include "Framework.h"
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
}

void Tilemap::Draw(Camera* pCamera)
{
    float baseX = m_Position.x;
    Vec2 tempPosition = m_Position;

    for (int i = 0; i < m_Width * m_Height; i++)
    {
        SpriteInfo* spriteInfo = m_pTileProperties[m_pLayout[i]].m_pSpriteInfo;

        m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, tempPosition, 0, m_pTexture, pCamera, m_pSpriteSheet->GetUVScale(spriteInfo->Name), m_pSpriteSheet->GetUVOffset(spriteInfo->Name));

        if ((i + 1) % m_Width == 0)
        {
            tempPosition.x = baseX;
            tempPosition.y += 3;
        }
        else
        {
            tempPosition.x += 2;
        }
    }
}

