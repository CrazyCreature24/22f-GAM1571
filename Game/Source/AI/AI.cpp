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

    //Filling Animation vector with sprites and their frame time
    m_MoveLeftAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("OctorocLeft1"), 0.2f));
    m_MoveLeftAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("OctorocLeft2"), 0.2f));
    m_MoveRightAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("OctorocRight1"), 0.2f));
    m_MoveRightAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("OctorocRight2"), 0.2f));
    m_MoveDownAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("OctorocDown1"), 0.2f));
    m_MoveDownAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("OctorocDown2"), 0.2f));
    m_MoveUpAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("OctorocUp1"), 0.2f));
    m_MoveUpAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("OctorocUp2"), 0.2f));

    //Assigning the sprites and stimes to their Animations
    m_Animations["WalkLeft"] = new FlipBook(m_MoveLeftAnim);
    m_Animations["WalkRight"] = new FlipBook(m_MoveRightAnim);
    m_Animations["WalkUp"] = new FlipBook(m_MoveUpAnim);
    m_Animations["WalkDown"] = new FlipBook(m_MoveDownAnim);

    //Setting the default Sprite
    m_pActiveSprite = m_Animations["WalkDown"]->GetActiveSprite();

    m_pMethodPointer = &AI::AIStateIdle;
    //ImGui::Text("Idle");

    m_TileSize = m_pTilemap->GetTileSize();

    m_Scale = m_TileSize;

    m_Position = { 1 * m_TileSize.x, 1 * m_TileSize.y };

    m_NextDestination = m_Destination1;
}

AI::~AI()
{
    for (auto& it : m_Animations)
    {
        delete it.second;
    }

    for (auto& it : m_MoveLeftAnim)
    {
        delete it;
    }

    for (auto& it : m_MoveRightAnim)
    {
        delete it;
    }

    for (auto& it : m_MoveUpAnim)
    {
        delete it;
    }

    for (auto& it : m_MoveDownAnim)
    {
        delete it;
    }
}

void AI::Update(float deltaTime)
{
    for (auto& it : m_Animations)
    {
        it.second->Update(deltaTime);
    }

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
    //I am aware this is a mess, but it works.
   
    std::vector<int> path;
    
    iVec2 tilePosition;

    //This finds out which direction the sprite is traveling and gets its tilePosition.
    //Also handles Animation. 
    //(I am going to tackle and Animation class to do more of the work behind the scenes over the break)
    if (m_Position.x - m_LastFramePosition.x < 0)
    {
        tilePosition = m_pTilemap->GetTilePositionFromWorldPosition(Vec2(m_Position.x + m_pTilemap->GetTileSize().x, m_Position.y));
        m_Animations["WalkLeft"]->Animation();
        m_pActiveSprite = m_Animations["WalkLeft"]->GetActiveSprite();
    }
    else if (m_Position.y - m_LastFramePosition.y < 0)
    {
        tilePosition = m_pTilemap->GetTilePositionFromWorldPosition(Vec2(m_Position.x, m_Position.y + m_pTilemap->GetTileSize().y));
        m_Animations["WalkDown"]->Animation();
        m_pActiveSprite = m_Animations["WalkDown"]->GetActiveSprite();
    }
    else
    {
        tilePosition = m_pTilemap->GetTilePositionFromWorldPosition(m_Position);
        if (m_Position.y - m_LastFramePosition.y > 0)
        {
            m_Animations["WalkUp"]->Animation();
            m_pActiveSprite = m_Animations["WalkUp"]->GetActiveSprite();
        }
        else if (m_Position.x - m_LastFramePosition.x > 0)
        {
            m_Animations["WalkRight"]->Animation();
            m_pActiveSprite = m_Animations["WalkRight"]->GetActiveSprite();
        }
    }

    m_LastFramePosition = m_Position;

    //If a path is found, it moves toward it this frame.
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
            //This prevents overshooting a position when it reaches the tile.
            m_Position = m_NextWorldPosition;
        }
        else
        {
            m_Position += (m_NextWorldPosition - m_Position).Normalize() * (m_Speed * deltaTime);
        }
    }
    
    //This deals with the change of Patrol point
    if (tilePosition == m_NextDestination)
    {
        m_pMethodPointer = &AI::AIStateIdle;
        //ImGui::Text("Idle");

        if (m_NextDestination == m_Destination1)
        {
            m_NextDestination = m_Destination2;
        }
        else if (m_NextDestination == m_Destination2)
        {
            m_NextDestination = m_Destination3;
        }
        else if (m_NextDestination == m_Destination3)
        {
            m_NextDestination = m_Destination4;
        }
        else if (m_NextDestination == m_Destination4)
        {
            m_NextDestination = m_Destination1;
        }
    }

}
