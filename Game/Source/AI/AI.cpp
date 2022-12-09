#include "Framework.h"
#include "../GameObject.h"
#include "../Tilemap.h"
#include "Pathfinder.h"
#include "AI.h"

AI::AI(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture, SpriteSheet* pSpriteSheet, Tilemap* pTilemap)
{
    m_pMesh = pMesh;
    m_pShaderProgram = pShaderProgram;
    m_pTexture = pTexture;
    m_pSpriteSheet = pSpriteSheet;
    m_pTilemap = pTilemap;

    m_pActiveSprite = m_pSpriteSheet->GetSpriteInfo("OldGuy1");

    m_pMethodPointer = &AI::AIStateIdle;
    //ImGui::Text("Idle");

    m_Position = { 1, 1 };

    m_NextDestination = m_Destination1;
}

AI::~AI()
{

}

void AI::Update(float deltaTime)
{
    (this->*m_pMethodPointer)(deltaTime);
}

void AI::Draw(Camera* pCamera)
{
    m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, 0, m_pTexture, pCamera, m_pSpriteSheet->GetUVScale(m_pActiveSprite->Name), m_pSpriteSheet->GetUVOffset(m_pActiveSprite->Name));

}

void AI::AIStateIdle(float deltaTime)
{
    m_IdleTimer += deltaTime;

    if (m_IdleTimer >= 2.0f)
    {
        m_pMethodPointer = &AI::AIStateWalking;
       // ImGui::Text("Walking");
        m_IdleTimer = 0.0f;
    }
}

void AI::AIStateWalking(float deltaTime)
{
    std::vector<int> path;
    

    iVec2 tilePosition = m_pTilemap->GetTilePositionFromWorldPosition(m_Position);

    bool PathFound = m_pTilemap->GetPathfinder()->FindPath(tilePosition.x, tilePosition.y, m_NextDestination.x, m_NextDestination.y);

    if (PathFound)
    {
        path = m_pTilemap->GetPathfinder()->GetPath(m_NextDestination.x, m_NextDestination.y);
        
        if (path.size() >= 2)
        {
            m_NextTileLocation = m_pTilemap->GetTilePositionFromIndex(*(path.end() - 2));
        }
        else
        {
            m_NextTileLocation = m_pTilemap->GetTilePositionFromIndex(*(path.begin()));
        }

        m_NextWorldPosition = m_pTilemap->GetWorldPositionFromTilePosition(m_NextTileLocation);

        float deltaX = m_NextWorldPosition.x - m_Position.x;
        float deltaY = m_NextWorldPosition.y - m_Position.y;

        if (abs(deltaX) < 0.2f && abs(deltaY) < 0.2f)
        {
            m_Position = m_NextWorldPosition;
        }
        else
        {
            m_Position += (m_NextWorldPosition - m_Position).Normalize() * (m_Speed * deltaTime);
        }
    }
    
    if (tilePosition.x == m_NextDestination.x && tilePosition.y == m_NextDestination.y)
    {
        m_pMethodPointer = &AI::AIStateIdle;
        //ImGui::Text("Idle");

        if (m_NextDestination.x == m_Destination1.x && m_NextDestination.y == m_Destination1.y)
        {
            m_NextDestination = m_Destination2;
        }
        else if (m_NextDestination.x == m_Destination2.x && m_NextDestination.y == m_Destination2.y)
        {
            m_NextDestination = m_Destination3;
        }
        else if (m_NextDestination.x == m_Destination3.x && m_NextDestination.y == m_Destination3.y)
        {
            m_NextDestination = m_Destination4;
        }
        else if (m_NextDestination.x == m_Destination4.x && m_NextDestination.y == m_Destination4.y)
        {
            m_NextDestination = m_Destination1;
        }
    }

}
