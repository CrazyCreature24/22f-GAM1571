#include "Framework.h"
#include "GameObject.h"
#include "VirtualController.h"
#include "Tilemap.h"
#include "Player.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture, SpriteSheet* pSpriteSheet, Tilemap* pTilemap)
{
    m_pMesh = pMesh;
    m_pShaderProgram = pShaderProgram;
    m_pTexture = pTexture;
    m_pSpriteSheet = pSpriteSheet;
    m_pTilemap = pTilemap;

    //Filling Animation vector with sprites and their frame time
    m_MoveLeftAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkLeft1"), 0.2f));
    m_MoveLeftAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkLeft2"), 0.2f));
    m_MoveRightAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkRight1"), 0.2f));
    m_MoveRightAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkRight2"), 0.2f));
    m_MoveDownAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkDown1"), 0.2f));
    m_MoveDownAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkDown2"), 0.2f));
    m_MoveUpAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkUp1"), 0.2f));
    m_MoveUpAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkUp2"), 0.2f));

    //Assigning the sprites and stimes to their Animations
    m_Animations["WalkLeft"] = new FlipBook(m_MoveLeftAnim);
    m_Animations["WalkRight"] = new FlipBook(m_MoveRightAnim);
    m_Animations["WalkUp"] = new FlipBook(m_MoveUpAnim);
    m_Animations["WalkDown"] = new FlipBook(m_MoveDownAnim);

    //Setting the default Sprite
    m_pActiveSprite = m_Animations["WalkDown"]->GetActiveSprite();

    m_Position = Vec2(3, 3);
    
}

Player::~Player()
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

void Player::Update(float deltaTime)
{
    for (auto& it : m_Animations)
    {
        it.second->Update(deltaTime);
    }
}

void Player::Draw(Camera* pCamera)
{
    //If the Player is active, Draw it
    if (!m_IsActive)
        return;

    m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, 0, m_pTexture, pCamera, m_pSpriteSheet->GetUVScale(m_pActiveSprite->Name), m_pSpriteSheet->GetUVOffset(m_pActiveSprite->Name));
}

void Player::OnKeyEvent(VirtualController* controller, float deltaTime)
{
    //If the Player is active, allow control to the player
    if (m_IsActive)
    {
        iVec2 tilePosition = m_pTilemap->GetTilePositionFromWorldPosition(m_Position);
        Vec2 newPos;

        //Movement
        if (controller->IsHeld(VirtualController::Action::Right)) // D or Right Arrow
        {
            newPos = m_Position + Vec2(5.0f * deltaTime, 0);

            m_Animations["WalkRight"]->Animation();
            m_pActiveSprite = m_Animations["WalkRight"]->GetActiveSprite();

            Vec2 newWorldPositionRight = newPos + Vec2(1, 0);
            if (m_pTilemap->GetTilePropertiesAtWorldPosition(Vec2(newWorldPositionRight.x, newWorldPositionRight.y)).m_Walkable)
            {
                m_Position = newPos;
            }
        }
        else if (controller->IsHeld(VirtualController::Action::Left)) // A or Left arrow
        {
            newPos = m_Position - Vec2(5.0f * deltaTime, 0);

            m_Animations["WalkLeft"]->Animation();
            m_pActiveSprite = m_Animations["WalkLeft"]->GetActiveSprite();

            Vec2 newWorldPositionLeft = newPos;
            if (m_pTilemap->GetTilePropertiesAtWorldPosition(Vec2(newWorldPositionLeft.x, newWorldPositionLeft.y)).m_Walkable)
            {
                m_Position = newPos;
            }
        }

        if (controller->IsHeld(VirtualController::Action::Up)) // W or Up arrow
        {
            newPos = m_Position + Vec2(0, 5.0f * deltaTime);

            m_Animations["WalkUp"]->Animation();
            m_pActiveSprite = m_Animations["WalkUp"]->GetActiveSprite();

            Vec2 newTilePositionUp = newPos + Vec2(0, 1);
            if (m_pTilemap->GetTilePropertiesAtWorldPosition(Vec2(newTilePositionUp.x + (m_pTilemap->GetTileSize().x * 0.5f), newTilePositionUp.y)).m_Walkable)
            {
                m_Position = newPos;
            }
        }
        else if (controller->IsHeld(VirtualController::Action::Down)) // S or Down arrow
        {
            newPos = m_Position - Vec2(0, 5.0f * deltaTime);

            m_Animations["WalkDown"]->Animation();
            m_pActiveSprite = m_Animations["WalkDown"]->GetActiveSprite();

            Vec2 newTilePositionDown = newPos;
            if (m_pTilemap->GetTilePropertiesAtWorldPosition(Vec2(newTilePositionDown.x + (m_pTilemap->GetTileSize().x * 0.5f), newTilePositionDown.y)).m_Walkable)
            {
                m_Position = newPos;
            }
        }

        //Scale
        if (controller->IsHeld(VirtualController::Action::ScaleUpX)) // K 
        {
            m_Scale.x += 2.0f * deltaTime;
        }
        else if (controller->IsHeld(VirtualController::Action::ScaleDownX)) // H
        {
            m_Scale.x += -2.0f * deltaTime;
        }

        if (controller->IsHeld(VirtualController::Action::ScaleUpY)) // U
        {
            m_Scale.y += 2.0f * deltaTime;
        }
        else if (controller->IsHeld(VirtualController::Action::ScaleDownY)) // J
        {
            m_Scale.y += -2.0f * deltaTime;
        }
    }
}


