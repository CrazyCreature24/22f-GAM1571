#include "Framework.h"
#include "GameObject.h"
#include "VirtualController.h"
#include "Player.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::Texture* pTexture, SpriteSheet* pSpriteSheet)
{
    m_pMesh = pMesh;
    m_pShaderProgram = pShaderProgram;
    m_pTexture = pTexture;
    m_pSpriteSheet = pSpriteSheet;

    m_Sprites["LinkWalkLeft1"] = new SpriteInfo("LinkWalkLeft1", m_pSpriteSheet->GetUVScale("LinkWalkLeft1"), m_pSpriteSheet->GetUVOffset("LinkWalkLeft1"));
    m_Sprites["LinkWalkRight1"] = new SpriteInfo("LinkWalkRight1", m_pSpriteSheet->GetUVScale("LinkWalkRight1"), m_pSpriteSheet->GetUVOffset("LinkWalkRight1"));
    m_Sprites["LinkWalkDown1"] = new SpriteInfo("LinkWalkDown1", m_pSpriteSheet->GetUVScale("LinkWalkDown1"), m_pSpriteSheet->GetUVOffset("LinkWalkDown1"));
    m_Sprites["LinkWalkUp1"] = new SpriteInfo("LinkWalkUp1", m_pSpriteSheet->GetUVScale("LinkWalkUp1"), m_pSpriteSheet->GetUVOffset("LinkWalkUp1"));

    m_pActiveSprite = m_Sprites["LinkWalkDown1"];
}

Player::~Player()
{
    for (auto& it : m_Sprites)
    {
        delete it.second;
    }

}

void Player::Update(float deltaTime)
{

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
        m_pActiveSprite = m_Sprites["LinkWalkRight1"];
    }
    else if (controller->IsHeld(VirtualController::Action::Left)) // A or Left arrow
    {
        m_Position.x += -5.0f * deltaTime;
        m_pActiveSprite = m_Sprites["LinkWalkLeft1"];
    }

    if (controller->IsHeld(VirtualController::Action::Up)) // W or Up arrow
    {
        m_Position.y += 5.0f * deltaTime;
        m_pActiveSprite = m_Sprites["LinkWalkUp1"];
    }
    else if (controller->IsHeld(VirtualController::Action::Down)) // S or Down arrow
    {
        m_Position.y += -5.0f * deltaTime;
        m_pActiveSprite = m_Sprites["LinkWalkDown1"];
    }
}


