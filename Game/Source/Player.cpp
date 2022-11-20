#include "Framework.h"
#include "GameObject.h"
#include "VirtualController.h"
#include "Player.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture, SpriteSheet* pSpriteSheet) : GameObject(pMesh, pShaderProgram, 0, pTexture, pSpriteSheet)
{
    m_MoveLeftAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkLeft1"), 0.2f));
    m_MoveLeftAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkLeft2"), 0.2f));
    m_MoveRightAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkRight1"), 0.2f));
    m_MoveRightAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkRight2"), 0.2f));
    m_MoveDownAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkDown1"), 0.2f));
    m_MoveDownAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkDown2"), 0.2f));
    m_MoveUpAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkUp1"), 0.2f));
    m_MoveUpAnim.push_back(new fw::SpriteAnimInfo(m_pSpriteSheet->GetSpriteInfo("LinkWalkUp2"), 0.2f));

    m_FlipBooks["WalkLeft"] = new FlipBook(m_MoveLeftAnim);
    m_FlipBooks["WalkRight"] = new FlipBook(m_MoveRightAnim);
    m_FlipBooks["WalkUp"] = new FlipBook(m_MoveUpAnim);
    m_FlipBooks["WalkDown"] = new FlipBook(m_MoveDownAnim);

    m_pActiveSprite = m_FlipBooks["WalkDown"]->GetActiveSprite();
    
}

Player::~Player()
{

    for (auto& it : m_FlipBooks)
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

    for (auto& it : m_FlipBooks)
    {
        it.second->Update(deltaTime);
    }
}

void Player::Draw(Camera* pCamera)
{
    if (!m_IsActive)
        return;

    m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, 0, m_pTexture, pCamera, m_pSpriteSheet, m_pActiveSprite);
}

void Player::OnKeyEvent(VirtualController* controller, float deltaTime)
{
    if (m_IsActive)
    {
        //Movement
        if (controller->IsHeld(VirtualController::Action::Right)) // D or Right Arrow
        {
            m_Position.x += 5.0f * deltaTime;

            if (controller->WasNewlyPressed(VirtualController::Action::Right))
            {
                m_FlipBooks["WalkRight"]->ResetElapsed();
            }

            m_FlipBooks["WalkRight"]->Animation();
            m_pActiveSprite = m_FlipBooks["WalkRight"]->GetActiveSprite();

        }
        else if (controller->IsHeld(VirtualController::Action::Left)) // A or Left arrow
        {
            m_Position.x += -5.0f * deltaTime;

            if (controller->WasNewlyPressed(VirtualController::Action::Left))
            {
                m_FlipBooks["WalkLeft"]->ResetElapsed();
            }

            m_FlipBooks["WalkLeft"]->Animation();
            m_pActiveSprite = m_FlipBooks["WalkLeft"]->GetActiveSprite();
        }

        if (controller->IsHeld(VirtualController::Action::Up)) // W or Up arrow
        {
            m_Position.y += 5.0f * deltaTime;

            if (controller->WasNewlyPressed(VirtualController::Action::Up))
            {
                m_FlipBooks["WalkUp"]->ResetElapsed();
            }

            m_FlipBooks["WalkUp"]->Animation();
            m_pActiveSprite = m_FlipBooks["WalkUp"]->GetActiveSprite();
        }
        else if (controller->IsHeld(VirtualController::Action::Down)) // S or Down arrow
        {
            m_Position.y += -5.0f * deltaTime;

            if (controller->WasNewlyPressed(VirtualController::Action::Down))
            {
                m_FlipBooks["WalkDown"]->ResetElapsed();
            }

            m_FlipBooks["WalkDown"]->Animation();
            m_pActiveSprite = m_FlipBooks["WalkDown"]->GetActiveSprite();
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


