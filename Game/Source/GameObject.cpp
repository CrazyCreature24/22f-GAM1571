#include "Framework.h"
#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, float timeElapsed, fw::Texture* pTexture, SpriteSheet* pSpriteSheet, const char* spriteName)
{
	m_pMesh = pMesh;
	m_pShaderProgram = pShaderProgram;
	m_TimeElapsed = timeElapsed;
	m_pTexture = pTexture;
	m_pSpriteSheet = pSpriteSheet;
	m_pSpriteName = spriteName;
}

GameObject::~GameObject()
{
	
}

void GameObject::Update(float deltaTime)
{

}

void GameObject::Draw(Camera* pCamera)
{
	m_pMesh->Draw(m_pShaderProgram, m_Scale, m_Angle, m_Position, m_TimeElapsed, m_pTexture, pCamera, m_pSpriteSheet->GetUVScale(m_pSpriteName), m_pSpriteSheet->GetUVOffset(m_pSpriteName));
}
