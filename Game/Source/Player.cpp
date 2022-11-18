#include "Framework.h"
#include "GameObject.h"
#include "VirtualController.h"
#include "Player.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture, SpriteSheet* pSpriteSheet) : GameObject(pMesh, pShaderProgram, 0, pTexture, pSpriteSheet)
{
    //m_pMesh = pMesh;
    //m_pShaderProgram = pShaderProgram;
    //m_pTexture = pTexture;
    //m_pSpriteSheet = pSpriteSheet;

    //m_FlipBooks["left"] = { "LinkWalkLeft1", "LinkWalkLeft2" };
    //m_FlipBooks["right"] = { {"LinkWalkRight1", 0.5f}, {"LinkWalkRight2",0.3f}, "LinkWalkRight3", "LinkWalkRight4" };

    m_MoveLeft.push_back(new SpriteInfo("LinkWalkLeft1", m_pSpriteSheet->GetUVScale("LinkWalkLeft1"), m_pSpriteSheet->GetUVOffset("LinkWalkLeft1")));
    m_MoveLeft.push_back(new SpriteInfo("LinkWalkLeft2", m_pSpriteSheet->GetUVScale("LinkWalkLeft2"), m_pSpriteSheet->GetUVOffset("LinkWalkLeft2")));
    m_MoveRight.push_back(new SpriteInfo("LinkWalkRight1", m_pSpriteSheet->GetUVScale("LinkWalkRight1"), m_pSpriteSheet->GetUVOffset("LinkWalkRight1")));
    m_MoveRight.push_back(new SpriteInfo("LinkWalkRight2", m_pSpriteSheet->GetUVScale("LinkWalkRight2"), m_pSpriteSheet->GetUVOffset("LinkWalkRight2")));
    m_MoveDown.push_back(new SpriteInfo("LinkWalkDown1", m_pSpriteSheet->GetUVScale("LinkWalkDown1"), m_pSpriteSheet->GetUVOffset("LinkWalkDown1")));
    m_MoveDown.push_back(new SpriteInfo("LinkWalkDown2", m_pSpriteSheet->GetUVScale("LinkWalkDown2"), m_pSpriteSheet->GetUVOffset("LinkWalkDown2")));
    m_MoveUp.push_back(new SpriteInfo("LinkWalkUp1", m_pSpriteSheet->GetUVScale("LinkWalkUp1"), m_pSpriteSheet->GetUVOffset("LinkWalkUp1")));
    m_MoveUp.push_back(new SpriteInfo("LinkWalkUp2", m_pSpriteSheet->GetUVScale("LinkWalkUp2"), m_pSpriteSheet->GetUVOffset("LinkWalkUp2")));

    m_MoveLeftAnim.push_back(new fw::SpriteAnimInfo(m_MoveLeft[0], 0.5f));
    m_MoveLeftAnim.push_back(new fw::SpriteAnimInfo(m_MoveLeft[1], 0.5f));
    m_MoveRightAnim.push_back(new fw::SpriteAnimInfo(m_MoveRight[0], 0.5f));
    m_MoveRightAnim.push_back(new fw::SpriteAnimInfo(m_MoveRight[1], 0.5f));
    m_MoveDownAnim.push_back(new fw::SpriteAnimInfo(m_MoveDown[0], 0.5f));
    m_MoveDownAnim.push_back(new fw::SpriteAnimInfo(m_MoveDown[1], 0.5f));
    m_MoveUpAnim.push_back(new fw::SpriteAnimInfo( m_MoveUp[0], 0.5f));
    m_MoveUpAnim.push_back(new fw::SpriteAnimInfo( m_MoveUp[1], 0.5f));

    m_FlipBooks["WalkLeft"] = new FlipBook(m_MoveLeftAnim);
    m_FlipBooks["WalkRight"] = new FlipBook(m_MoveRightAnim);
    m_FlipBooks["WalkUp"] = new FlipBook(m_MoveUpAnim);
    m_FlipBooks["WalkDown"] = new FlipBook(m_MoveDownAnim);

    m_pActiveSprite = m_FlipBooks["WalkDown"]->GetActiveSprite();
    
}

Player::~Player()
{
    for (auto& it : m_Sprites)
    {
        delete it.second;
    }

    for (auto& it : m_FlipBooks)
    {
        delete it.second;
    }

    for (auto& it : m_MoveLeft)
    {
        delete it;
    }

    for (auto& it : m_MoveRight)
    {
        delete it;
    }

    for (auto& it : m_MoveUp)
    {
        delete it;
    }

    for (auto& it : m_MoveDown)
    {
        delete it;
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
    m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, 0, m_pTexture, pCamera, m_pSpriteSheet, m_pActiveSprite);
}

void Player::OnKeyEvent(VirtualController* controller, float deltaTime)
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


