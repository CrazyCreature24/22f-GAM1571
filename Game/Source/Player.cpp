#include "Framework.h"
#include "GameObject.h"
#include "VirtualController.h"
#include "Player.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture, SpriteSheet* pSpriteSheet) : GameObject(pMesh, pShaderProgram, 0, pTexture, pSpriteSheet)
{
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

    m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, 0, m_pTexture, pCamera, m_pSpriteSheet, m_pActiveSprite);
}

void Player::OnKeyEvent(VirtualController* controller, float deltaTime)
{
    //If the Player is active, allow control to the player
    if (m_IsActive)
    {
        //Movement
        if (controller->IsHeld(VirtualController::Action::Right)) // D or Right Arrow
        {
            m_Position.x += 5.0f * deltaTime;

            //Resets the Animation time
            if (controller->WasNewlyPressed(VirtualController::Action::Right))
            {
                m_Animations["WalkRight"]->ResetElapsed();
            }

            m_Animations["WalkRight"]->Animation();
            m_pActiveSprite = m_Animations["WalkRight"]->GetActiveSprite();

        }
        else if (controller->IsHeld(VirtualController::Action::Left)) // A or Left arrow
        {
            m_Position.x += -5.0f * deltaTime;

            if (controller->WasNewlyPressed(VirtualController::Action::Left))
            {
                m_Animations["WalkLeft"]->ResetElapsed();
            }

            m_Animations["WalkLeft"]->Animation();
            m_pActiveSprite = m_Animations["WalkLeft"]->GetActiveSprite();
        }

        if (controller->IsHeld(VirtualController::Action::Up)) // W or Up arrow
        {
            m_Position.y += 5.0f * deltaTime;

            if (controller->WasNewlyPressed(VirtualController::Action::Up))
            {
                m_Animations["WalkUp"]->ResetElapsed();
            }

            m_Animations["WalkUp"]->Animation();
            m_pActiveSprite = m_Animations["WalkUp"]->GetActiveSprite();
        }
        else if (controller->IsHeld(VirtualController::Action::Down)) // S or Down arrow
        {
            m_Position.y += -5.0f * deltaTime;

            if (controller->WasNewlyPressed(VirtualController::Action::Down))
            {
                m_Animations["WalkDown"]->ResetElapsed();
            }

            m_Animations["WalkDown"]->Animation();
            m_pActiveSprite = m_Animations["WalkDown"]->GetActiveSprite();
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


